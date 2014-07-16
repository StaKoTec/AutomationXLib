// This is the main DLL file.

#include "stdafx.h"

#include "AX.h"

namespace AutomationX
{
	bool AX::Connected::get()
	{ 
		return AxIsRunning() && AxIsHostMaster();
	}

	AX::AX()
	{
		AxInit(); //First function to call
		//AxOmAttachToObjectMemory must be called after AxInit
		if (!AxOmAttachToObjectMemory()) throw gcnew AXException("Could not attach to shared memory. Make sure AutomationX is running and the user running this program has enough privileges.");
		AxOmQueryProcessGroupInfo(); //No interpretable return value, must be called after AxOmAttachToObjectMemory
		_spsId = new int;
		SpsIdChanged();
		_workerTimer = gcnew Timers::Timer(1000);
		_workerTimer->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &AutomationX::AX::OnWorkerTimerElapsed);
		_workerTimer->Start();
	}

	AX::~AX()
	{
		if (_spsId)	delete _spsId;
	}

	void AX::OnWorkerTimerElapsed(System::Object ^sender, System::Timers::ElapsedEventArgs ^e)
	{
		if (AxShutdownEvent() == 1 || !Connected) OnShutdown(this);
	}

	void AX::CheckRunning()
	{
		if (!Connected) throw gcnew AXNotRunningException("aX is not running.");
	}

	void AX::Shutdown()
	{
		OnShutdown(this);
		AxSendShutdownEvent();
	}

	System::Collections::Generic::List<String^>^ AX::GetInstanceNames(String^ className)
	{
		System::Collections::Generic::List<String^>^ instanceNames = gcnew System::Collections::Generic::List<String^>();
		char* cName = _converter.GetCString(className);
		AX_INSTANCE data = nullptr;
		while (data = AxGetInstance(data, cName))
		{
			String^ instanceName = gcnew String(AxGetInstanceName(data));
			if (instanceName->Length == 0) continue;
			instanceNames->Add(instanceName);
		}
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		return instanceNames;
	}

	bool AX::SpsIdChanged()
	{
		if (AxHasSpsIdChanged(_spsId) == 1)
		{
			OnSpsIdChanged(this);
			return true;
		}
		return false;
	}
}
