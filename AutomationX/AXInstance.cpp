#include "stdafx.h"
#include "AXInstance.h"

namespace AutomationX
{
	String^ AXInstance::Remark::get()
	{
		_ax->SpsIdChanged();
		char* cName = _converter.GetCString(_name);
		void* handle = AxQueryInstance(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXInstanceException("Could not get instance handle."));
		String^ value = gcnew String(AxGetInstanceRemark(handle));
		return value;
	}

	/*void AXInstance::Remark::set(String^ value)
	{
		_ax->SpsIdChanged();
		char* cName = _converter.GetCString(_name);
		void* handle = AxQueryInstance(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw gcnew AXVariableException("Could not get instance handle.");
		std::string temp = _converter.GetString(value);
		char* remark = new char[temp.size() + 1];
		strcpy_s(remark, temp.size() + 1, temp.c_str());
		if (!AxSetInstanceRemark(handle, remark)) throw gcnew AXVariableException("Could not set remark.");
		delete[] remark;
	}*/

	void AXInstance::Status::set(String^ value)
	{
		_ax->SpsIdChanged();
		OnStatus(this, value);
		if (_statusVariable == nullptr) return;
		_statusVariable->Set(value);
	}

	void AXInstance::Error::set(String^ value)
	{
		_ax->SpsIdChanged();
		OnError(this, value);
		if (_alarmVariable == nullptr) return;
		_alarmVariable->Set(true);
		if (_alarmTextVariable == nullptr) return;
		_alarmTextVariable->Set(value);
	}

	bool AXInstance::VariableEvents::get()
	{
		return _variableEvents;
	}

	void AXInstance::VariableEvents::set(bool value)
	{
		try
		{
			_workerTimerMutex.WaitOne();
			if (value)
			{
				_variableEvents = true;
				GetVariables();
				if (_workerTimer) _workerTimer->Stop();
				_stopWorkerTimer = false;
				_workerTimer = gcnew Timers::Timer(PollingInterval);
				_workerTimer->AutoReset = true;
				_workerTimer->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &AXInstance::Worker);
				_workerTimer->Start();
			}
			else
			{
				_variableEvents = false;
				_stopWorkerTimer = true;
				if (_workerTimer) _workerTimer->Stop();
			}
			_workerTimerMutex.ReleaseMutex();
		}
		catch (const Exception^ ex)
		{
			_workerTimerMutex.ReleaseMutex();
			throw ex;
		}
	}

	array<AXVariable^>^ AXInstance::Variables::get()
	{
		_ax->SpsIdChanged();
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
		_ax->OnSpsIdChanged += gcnew AX::SpsIdChangedEventHandler(this, &AXInstance::OnSpsIdChanged);
	}

	AXInstance::AXInstance(AX^ ax, String^ name, String^ statusVariableName, String^ alarmVariableName) : AXInstance(ax, name)
	{
		try
		{
			if(statusVariableName->Length > 0) _statusVariable = Get(statusVariableName);
		}
		catch (const AXVariableException^) { throw gcnew AXInstanceException("Could not get status variable.");	}
		if (alarmVariableName->Length > 0)
		{
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
	}

	AXInstance::~AXInstance()
	{
	}

	void AXInstance::Worker(System::Object ^sender, System::Timers::ElapsedEventArgs ^e)
	{
		try
		{
			_workerTimerMutex.WaitOne();
			DateTime time;
			Int32 timeToSleep = 0;
			time = DateTime::Now;
			try
			{
				_ax->SpsIdChanged();
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
			if (!_stopWorkerTimer) _workerTimer->Start();
			_workerTimerMutex.ReleaseMutex();
		}
		catch (const Exception^ ex)
		{
			_workerTimerMutex.ReleaseMutex();
			throw ex;
		}
	}

	void AXInstance::GetVariables()
	{
		try
		{
			if (_variableListMutex.WaitOne(10000))
			{
				_variableList->Clear();
				char* cName = _converter.GetCString(_name);
				void* handle = AxQueryInstance(cName);
				Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
				if (!handle) throw gcnew AXInstanceException("Could not get instance handle.");
				//Don't call _ax->SpsIdChanged here as it causes a call to GetVariables again!
				AX_VAR_DSC data = 0;
				while (data = AxVarDscFromInstance(handle, data))
				{
					String^ name = gcnew String(AxGetNameFromVarDSC(data));
					if (name->Length == 0) continue;
					AXVariable^ variable;
					if (_variables->ContainsKey(name))
					{
						variable = _variables[name];
					}
					else
					{
						try
						{
							variable = gcnew AXVariable(this, name);
						}
						catch (const AXVariableTypeException^) { continue; }
						variable->Refresh();
						variable->OnValueChanged += gcnew AXVariable::ValueChangedEventHandler(this, &AXInstance::ValueChanged);
						variable->OnArrayValueChanged += gcnew AXVariable::ArrayValueChangedEventHandler(this, &AXInstance::ArrayValueChanged);
						_variables->Add(name, variable);
					}
					_variableList->Add(variable);
					
				}
				//Remove variables from _variables that don't exist anymore
				//We do this, so all already existing variables are not invalidated
				if (_variables->Count != _variableList->Count)
				{
					List<String^>^ elementsToRemove = gcnew List<String^>();
					for each (KeyValuePair<String^, AXVariable^> element in _variables)
					{
						if (!VariableExists(element.Key))
						{
							//Don't remove elements from _variables while we are iterating through it
							elementsToRemove->Add(element.Key);
						}
					}
					for each (String^ element in elementsToRemove)
					{
						_variables->Remove(element);
					}
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

	void AXInstance::ArrayValueChanged(AXVariable ^sender, UInt16 index)
	{
		OnArrayValueChanged(sender, index);
	}


	void AXInstance::ValueChanged(AXVariable ^sender)
	{
		OnVariableValueChanged(sender);
	}

	AXVariable^ AXInstance::Get(String^ variableName)
	{
		_ax->SpsIdChanged();
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
		_ax->SpsIdChanged();
		char* cName = _converter.GetCString(_name + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) return false;
		AxFreeExecData(handle);
		return true;
	}

	void AXInstance::OnSpsIdChanged(AX ^sender)
	{
		GetVariables();
	}
}
