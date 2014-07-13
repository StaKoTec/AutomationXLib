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
		_workerTimer = gcnew Timers::Timer(1000);
		_workerTimer->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &AutomationX::AX::OnWorkerTimerElapsed);
		_workerTimer->Start();
		if (instanceName->Length == 0) throw (AXException^)(gcnew AXException("Instance name is empty."));
		_instanceName = instanceName;
		if (!AxOmAttachToObjectMemory()) throw (AXException^)(gcnew AXException("Could not attach to shared memory."));
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
		if (AxShutdownEvent() == 1) OnShutdown();
	}

	/// <summary>Checks if aX is running.</summary>
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
		OnStatus(statusText);
		if (_statusVariableName->Length == 0) return;
		_writer->WriteString(_instanceName, _statusVariableName, statusText);
	}

	/// <summary>Sets the aX alarm variable provided with the constructor.</summary>
	/// <param name='errorText'>Text to set.</param>
	void AX::SetError(String^ errorText)
	{
		OnError(errorText);
		if (_alarmVariableName->Length == 0) return;
		_writer->WriteBool(_instanceName, _alarmVariableName, true);
		_writer->WriteString(_instanceName, _alarmVariableName + ".TEXT", errorText);
	}

	/// <summary>Tell aX to shut down.</summary>
	void AX::Shutdown()
	{
		OnShutdown();
		AxSendShutdownEvent();
	}
}
