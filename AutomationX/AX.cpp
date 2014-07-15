// This is the main DLL file.

#include "stdafx.h"

#include "AX.h"

namespace AutomationX
{
	/// <summary>Default constructor.</summary>
	/// <param name='instanceName'>Name of our aX instance.</param>
	AX::AX(String^ instanceName)
	{
		_statusVariableName = gcnew String("");
		_alarmVariableName = gcnew String("");
		_writer = gcnew AXWriter(this);
		if (instanceName->Length == 0) throw (AXException^)(gcnew AXException("Instance name is empty."));
		_instanceName = instanceName;
		AxInit(); //First function to call
		//AxOmAttachToObjectMemory must be called after AxInit
		if (!AxOmAttachToObjectMemory()) throw (AXException^)(gcnew AXException("Could not attach to shared memory. Make sure AutomationX is running and the user running this program has enough privileges."));
		AxOmQueryProcessGroupInfo(); //No interpretable return value, must be called after AxOmAttachToObjectMemory
		_workerTimer = gcnew Timers::Timer(1000);
		_workerTimer->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &AutomationX::AX::OnWorkerTimerElapsed);
		_workerTimer->Start();
	}

	/// <summary>Constructor taking names of status variables.</summary>
	/// <param name='instanceName'>Name of our aX instance.</param>
	/// <param name='statusVariableName'>Name of a status variable of type STRING to store status information.</param>
	/// <param name='alarmVariableName'>Name of a variable of type ALARM.</param>
	AX::AX(String^ instanceName, String^ statusVariableName, String^ alarmVariableName) : AX(instanceName)
	{
		_statusVariableName = statusVariableName;
		_alarmVariableName = alarmVariableName;
	}

	void AX::OnWorkerTimerElapsed(System::Object ^sender, System::Timers::ElapsedEventArgs ^e)
	{
		if (AxShutdownEvent() == 1 || !IsRunning()) OnShutdown(this);
	}

	/// <summary>Checks if aX is running and if the local computer is running as the master of a redundant master slave server configuration.</summary>
	/// <returns>true when aX is running, otherwise false.</returns>
	Boolean AX::IsRunning()
	{
		if (!AxIsRunning() || !AxIsHostMaster()) return false;
		return true;
	}

	/// <summary>Checks if aX is running.</summary>
	/// <returns>Throws AXNotRunningException when aX is not running.</returns>
	void AX::CheckRunning()
	{
		if (!IsRunning()) throw (AXNotRunningException^)(gcnew AXNotRunningException("aX is not running."));
	}

	/// <summary>Sets the aX status variable provided with the constructor.</summary>
	/// <param name='statusText'>Text to set.</param>
	void AX::SetStatus(String^ statusText)
	{
		OnStatus(this, statusText);
		if (_statusVariableName->Length == 0) return;
		_writer->WriteString(_instanceName, _statusVariableName, statusText);
	}

	/// <summary>Sets the aX alarm variable provided with the constructor.</summary>
	/// <param name='errorText'>Text to set.</param>
	void AX::SetError(String^ errorText)
	{
		OnError(this, errorText);
		if (_alarmVariableName->Length == 0) return;
		_writer->WriteBool(_instanceName, _alarmVariableName, true);
		_writer->WriteString(_instanceName, _alarmVariableName + ".TEXT", errorText);
	}

	/// <summary>Tell aX to shut down.</summary>
	void AX::Shutdown()
	{
		OnShutdown(this);
		AxSendShutdownEvent();
	}
}
