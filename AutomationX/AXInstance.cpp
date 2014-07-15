#include "stdafx.h"
#include "AXInstance.h"

namespace AutomationX
{
	String^ AXInstance::Remark::get()
	{
		char* cName = _converter.GetCString(_name);
		void* handle = AxQueryInstance(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXInstanceException("Could not get instance handle."));
		String^ value = gcnew String(AxGetInstanceRemark(handle));
		return value;
	}

	/// <summary>Sets the aX status variable provided with the constructor.</summary>
	/// <param name='value'>Text to set.</param>
	void AXInstance::Status::set(String^ value)
	{
		OnStatus(this, value);
		if (_statusVariable == nullptr) return;
		_statusVariable->Set(value);
	}

	/// <summary>Sets the aX alarm variable provided with the constructor.</summary>
	/// <param name='value'>Text to set.</param>
	void AXInstance::Error::set(String^ value)
	{
		OnError(this, value);
		if (_alarmVariable == nullptr) return;
		_alarmVariable->Set(true);
		if (_alarmTextVariable == nullptr) return;
		_alarmTextVariable->Set(value);
	}

	array<AXVariable^>^ AXInstance::Variables::get()
	{
		if (_variableList->Count == 0) GetVariables();

		array<AXVariable^>^ variables = nullptr;
		try
		{
			if (_variableListMutex.WaitOne(1000))
			{
				variables = gcnew array<AXVariable^>(_variableList->Count);
				_variableList->CopyTo(variables);
				_variableListMutex.ReleaseMutex();
			}
		}
		catch (const Exception^ ex)
		{
			_variableListMutex.ReleaseMutex();
			throw ex;
		}

		return variables;
	}

	AXVariable^ AXInstance::default::get(String^ variableName)
	{
		return Get(variableName);
	}

	AXInstance::AXInstance(AX^ ax, String^ name)
	{
		_ax = ax;
		if (name->Length == 0) throw (AXException^)(gcnew AXInstanceException("Instance name is empty."));
		_name = name;
		char* cName = _converter.GetCString(_name);
		void* handle = AxQueryInstance(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXInstanceException("Could not get instance handle."));
	}

	AXInstance::AXInstance(AX^ ax, String^ name, String^ statusVariableName, String^ alarmVariableName) : AXInstance(ax, name)
	{
		try
		{
			_statusVariable = Get(statusVariableName);
		}
		catch (const AXVariableException^) { throw gcnew AXInstanceException("Could not get status variable.");	}
		try
		{
			_alarmVariable = Get(alarmVariableName);
		}
		catch (const AXVariableException^) { throw gcnew AXInstanceException("Could not get alarm variable."); }
		try
		{
			_alarmTextVariable = Get(alarmVariableName + ".TEXT");
		}
		catch (const AXVariableException^) { throw gcnew AXInstanceException("Could not get alarm variable's \"TEXT\"."); }
	}

	AXInstance::~AXInstance()
	{
	}

	void AXInstance::Worker(System::Object ^sender, System::Timers::ElapsedEventArgs ^e)
	{
		DateTime time;
		Int32 timeToSleep = 0;
		time = DateTime::Now;
		try
		{
			if (_variableListMutex.WaitOne(1000))
			{
				for (int i = 0; i < _variableList->Count; i++)
				{
					_variableList[i]->Refresh(true);
				}
				_variableListMutex.ReleaseMutex();
			}
		}
		catch (const Exception^ ex)
		{
			_variableListMutex.ReleaseMutex();
			throw ex;
		}

		timeToSleep = _pollingInterval - DateTime::Now.Subtract(time).Milliseconds;
		if (timeToSleep < 10) timeToSleep = 10;
		_workerTimer->Interval = timeToSleep;
		if(!_stopWorkerTimer) _workerTimer->Start();
	}

	void AXInstance::GetVariables()
	{
		try
		{
			if (_variableListMutex.WaitOne(10000))
			{
				_variables->Clear();
				_variableList->Clear();
				char* cName = _converter.GetCString(_name);
				void* handle = AxQueryInstance(cName);
				Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
				if (!handle) throw gcnew AXInstanceException("Could not get instance handle.");

				AX_VAR_DSC data = 0;
				while (data = AxVarDscFromInstance(handle, data))
				{
					String^ name = gcnew String(AxGetNameFromVarDSC(data));
					if (name->Length == 0) continue;
					AXVariable^ variable;
					try
					{
						variable = gcnew AXVariable(this, name);
					}
					catch (const AXVariableTypeException^) { continue; }
					_variables->Add(name, variable);
					_variableList->Add(variable);
					variable->Refresh();
				}
				_variableListMutex.ReleaseMutex();
			}
		}
		catch (const Exception^ ex)
		{
			_variableListMutex.ReleaseMutex();
			throw ex;
		}
	}

	AXVariable^ AXInstance::Get(String^ variableName)
	{
		if (_variables->Count == 0) GetVariables();
		if (_variables->ContainsKey(variableName)) return _variables[variableName];
		if (variableName->IndexOf('.') > -1)
		{
			try
			{
				AXVariable^ variable = gcnew AXVariable(this, variableName);
				return variable;
			}
			catch (const AXVariableException^) {}
		}
		return nullptr;
	}

	bool AXInstance::VariableExists(String^ variableName)
	{
		char* cName = _converter.GetCString(_name + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) return false;
		AxFreeExecData(handle);
		return true;
	}

	void AXInstance::EnableVariableEvents()
	{
		GetVariables();
		if(_workerTimer) _workerTimer->Stop();
		_stopWorkerTimer = false;
		_workerTimer = gcnew Timers::Timer(PollingInterval);
		_workerTimer->AutoReset = true;
		_workerTimer->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &AXInstance::Worker);
		_workerTimer->Start();
	}

	void AXInstance::DisableVariableEvents()
	{
		_stopWorkerTimer = true;
		if (_workerTimer) _workerTimer->Stop();
	}
}