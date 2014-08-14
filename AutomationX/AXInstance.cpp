#include "stdafx.h"
#include "AXInstance.h"

namespace AutomationX
{
	String^ AXInstance::Remark::get()
	{
		_ax->CheckSpsId();
		void* handle = GetHandle();
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
		_ax->CheckSpsId();
		StatusEvent(this, value);
		if (_statusVariable == nullptr) return;
		_statusVariable->Set(value);
	}

	void AXInstance::Error::set(String^ value)
	{
		_ax->CheckSpsId();
		ErrorEvent(this, value);
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
			if (_disposed) return;
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
		_ax->CheckSpsId();
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

	array<AXInstance^>^ AXInstance::Subinstances::get()
	{
		_ax->CheckSpsId();
		if (_subinstanceList->Count == 0) GetSubinstances();

		array<AXInstance^>^ instances = nullptr;
		try
		{
			if (_subinstanceListMutex.WaitOne(1000))
			{
				instances = gcnew array<AXInstance^>(_subinstanceList->Count);
				_subinstanceList->CopyTo(instances);
				_subinstanceListMutex.ReleaseMutex();
			}
		}
		catch (const Exception^ ex)
		{
			_subinstanceListMutex.ReleaseMutex();
			throw ex;
		}

		return instances;
	}

	AXVariable^ AXInstance::default::get(String^ variableName)
	{
		return Get(variableName);
	}

	AXInstance::AXInstance(AX^ ax, String^ name) : AXInstance(ax, nullptr, name)
	{

	}

	AXInstance::AXInstance(AX^ ax, AXInstance^ parent, String^ name)
	{
		_parent = parent;
		_ax = ax;
		if (name->Length == 0) throw (AXException^)(gcnew AXInstanceException("Instance name is empty."));
		_name = name;
		void* handle = GetHandle();
		_spsIdChangedDelegate = gcnew AX::SpsIdChangedEventHandler(this, &AXInstance::OnSpsIdChanged);
		_variableValueChangedDelegate = gcnew AXVariable::ValueChangedEventHandler(this, &AXInstance::OnValueChanged);
		_arrayValueChangedDelegate = gcnew AXVariable::ArrayValueChangedEventHandler(this, &AXInstance::OnArrayValueChanged);
		_ax->SpsIdChanged += _spsIdChangedDelegate;
	}

	AXInstance::AXInstance(AX^ ax, String^ name, String^ statusVariableName, String^ alarmVariableName) : AXInstance(ax, name)
	{
		try
		{
			if (statusVariableName->Length > 0) _statusVariable = Get(statusVariableName);
		}
		catch (const AXVariableException^) { throw gcnew AXInstanceException("Could not get status variable."); }
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
		if (_disposed) return;
		_disposed = true;
		try
		{
			_stopWorkerTimer = true;
			_workerTimerMutex.WaitOne();
			{
				if (_workerTimer) _workerTimer->Stop();
				_workerTimer = nullptr;
			}
			_workerTimerMutex.ReleaseMutex();
		}
		catch (const Exception^ ex)
		{
			_workerTimerMutex.ReleaseMutex();
			throw ex;
		}
		_ax->SpsIdChanged -= _spsIdChangedDelegate;
		for each (AXVariable^ element in _variableList)
		{
			element->~AXVariable(); //Dispose all variables belonging to this object
		}
		_variableList->Clear();
		_variables->Clear();
		_ax = nullptr;
		//GC::Collect(); //Uncomment to check for memory leaks
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
				_ax->CheckSpsId();
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

	void* AXInstance::GetHandle()
	{
		char* cName = _converter.GetCString(_name);
		void* handle = _parent ? AxQueryInstanceFromParent(_parent->GetHandle(), cName) : AxQueryInstance(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw gcnew AXInstanceException("Could not get instance handle.");
		return handle;
	}

	void AXInstance::GetVariables()
	{
		try
		{
			if (_variableListMutex.WaitOne(10000))
			{
				_variableList->Clear();
				void* handle = GetHandle();
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
						variable->ValueChanged += _variableValueChangedDelegate;
						variable->ArrayValueChanged += _arrayValueChangedDelegate;
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
							element.Value->ValueChanged -= _variableValueChangedDelegate;
							element.Value->ArrayValueChanged -= _arrayValueChangedDelegate;
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

	void AXInstance::GetSubinstances()
	{
		try
		{
			if (_subinstanceListMutex.WaitOne(10000))
			{
				_subinstanceList->Clear();
				void* handle = GetHandle();
				//Don't call _ax->SpsIdChanged here as it causes a call to GetVariables again!
				AxSubInstanceList_StructPt pInstanceList = nullptr;
				int instanceCount = AxGetSubInstanceList(handle, &pInstanceList);
				if (instanceCount == 0) return;
				for (int i = 0; i < instanceCount; i++)
				{
					String^ name = gcnew String(pInstanceList[i].instancePath);
					if (name->Length == 0 || name->LastIndexOf('.') == -1) continue;
					name = name->Substring(name->LastIndexOf('.') + 1);
					AXInstance^ instance;
					if (_subinstances->ContainsKey(name))
					{
						instance = _subinstances[name];
					}
					else
					{
						instance = gcnew AXInstance(_ax, this, name);
						_subinstances->Add(name, instance);
					}
					_subinstanceList->Add(instance);
				}
				AxFreeSubInstanceList(&pInstanceList);
				//Remove instances from _subinstances that don't exist anymore
				//We do this, so all already existing subinstances are not invalidated
				if (_subinstances->Count != _subinstanceList->Count)
				{
					List<String^>^ elementsToRemove = gcnew List<String^>();
					for each (KeyValuePair<String^, AXInstance^> element in _subinstances)
					{
						if (!SubinstanceExists(element.Key))
						{
							//Don't remove elements from _subinstances while we are iterating through it
							elementsToRemove->Add(element.Key);
						}
					}
					for each (String^ element in elementsToRemove)
					{
						_subinstances->Remove(element);
					}
				}
				_subinstanceListMutex.ReleaseMutex();
			}
		}
		catch (const Exception^ ex)
		{
			_subinstanceListMutex.ReleaseMutex();
			throw ex;
		}
	}

	void AXInstance::OnArrayValueChanged(AXVariable ^sender, UInt16 index)
	{
		ArrayValueChanged(sender, index);
	}


	void AXInstance::OnValueChanged(AXVariable ^sender)
	{
		VariableValueChanged(sender);
	}

	AXVariable^ AXInstance::Get(String^ variableName)
	{
		_ax->CheckSpsId();
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

	AXInstance^ AXInstance::GetSubinstance(String^ instanceName)
	{
		_ax->CheckSpsId();
		if (_subinstances->Count == 0) GetSubinstances();
		if (_subinstances->ContainsKey(instanceName)) return _subinstances[instanceName];
		return nullptr;
	}

	bool AXInstance::VariableExists(String^ variableName)
	{
		_ax->CheckSpsId();
		char* cName = _converter.GetCString(_parent ? _parent->Name + "." + _name + "." + variableName : _name + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) return false;
		AxFreeExecData(handle);
		return true;
	}

	bool AXInstance::SubinstanceExists(String^ instanceName)
	{
		_ax->CheckSpsId();
		char* cName = _converter.GetCString(_name);
		void* handle = _parent ? AxQueryInstanceFromParent(_parent->GetHandle(), cName) : AxQueryInstance(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) return false;
		cName = _converter.GetCString(instanceName);
		void* handle2 = AxQueryInstanceFromParent(handle, cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle2) return false;
		return true;
	}

	void AXInstance::OnSpsIdChanged(AX ^sender)
	{
		GetVariables();
		GetSubinstances();
	}
}
