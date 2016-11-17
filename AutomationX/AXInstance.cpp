#include "stdafx.h"
#include "AxInstance.h"

namespace AutomationX
{
	array<AxVariable^>^ AxInstance::Variables::get()
	{
		array<AxVariable^>^ variables = nullptr;
		Lock variableGuard(_variableListMutex);
		variables = gcnew array<AxVariable^>(_variableList->Count);
		_variableList->CopyTo(variables);

		return variables;
	}

	array<AxInstance^>^ AxInstance::Subinstances::get()
	{
		array<AxInstance^>^ instances = nullptr;
		Lock subinstanceGuard(_subinstanceListMutex);
		instances = gcnew array<AxInstance^>(_subinstanceList->Count);
		_subinstanceList->CopyTo(instances);
		
		return instances;
	}

	AxVariable^ AxInstance::default::get(String^ variableName)
	{
		return Get(variableName);
	}

	AxInstance::AxInstance(Ax^ ax, String^ name) : AxInstance(ax, nullptr, name, true)
	{
	}

	AxInstance::AxInstance(Ax^ ax, AxInstance^ parent, String^ name) : AxInstance(ax, parent, name, true)
	{
	}

	AxInstance::AxInstance(Ax^ ax, String^ name, bool waitForInitCompleted) : AxInstance(ax, nullptr, name, waitForInitCompleted)
	{
	}

	AxInstance::AxInstance(Ax^ ax, AxInstance^ parent, String^ name, bool waitForInitCompleted)
	{
		_ax = ax;
		_parent = parent;
		if (name->Length == 0) throw gcnew AxInstanceException("Instance name is empty.");
		_name = name;
		_variableValueChangedDelegate = gcnew AxVariable::ValueChangedEventHandler(this, &AxInstance::OnValueChanged);
		_arrayValueChangedDelegate = gcnew AxVariable::ArrayValueChangedEventHandler(this, &AxInstance::OnArrayValueChanged);
		_spsIdChangedCallbackId = _ax->AddSpsIdChangedInstanceCallback(Binder::Bind(gcnew NoParameterReturnBoolDelegate(this, &AxInstance::SpsIdChanged)));
		if (!ReloadStaticProperties(waitForInitCompleted)) throw gcnew AxInstanceException("Could not get instance handle for " + _name);
	}

	AxInstance::~AxInstance()
	{
		this->!AxInstance();
	}

	AxInstance::!AxInstance()
	{
		_ax->RemoveSpsIdChangedInstanceCallback(_spsIdChangedCallbackId);
		Lock spsIdChangedGuard(_spsIdChangedMutex);
		{
			Lock variableGuard(_variableListMutex);
			for each (AxVariable^ element in _variableList)
			{
				element->~AxVariable(); //Dispose all variables belonging to this object
			}
			_variableList->Clear();
			_variables->Clear();
		}
		{
			Lock subinstanceGuard(_subinstanceListMutex);
			for each (AxInstance^ element in _subinstanceList)
			{
				element->~AxInstance(); //Dispose all subinstances belonging to this object
			}
			_subinstanceList->Clear();
			_subinstances->Clear();
		}
		_ax = nullptr;
	}

	void AxInstance::SetReloadRequired()
	{
		_reloadRequired = true;
		{
			Lock variableGuard(_variableListMutex);
			for each (AxVariable^ element in _variableList)
			{
				element->Events = false;
				element->SetCleanUp();
			}
		}

		{
			Lock subinstanceGuard(_subinstanceListMutex);
			for each (AxInstance^ element in _subinstanceList)
			{
				element->SetReloadRequired();
			}
		}
	}

	void AxInstance::SetCleanUp()
	{
		_cleanUp = true;
		{
			Lock variableGuard(_variableListMutex);
			for each (AxVariable^ element in _variableList)
			{
				element->Events = false;
				element->SetCleanUp();
			}
		}

		{
			Lock subinstanceGuard(_subinstanceListMutex);
			for each (AxInstance^ element in _subinstanceList)
			{
				element->SetCleanUp();
			}
		}
	}

	bool AxInstance::SpsIdChanged()
	{
		Lock spsIdChangedGuard(_spsIdChangedMutex);
		if (!GetRawHandle())
		{
			SetCleanUp();
			return false;
		}
		InvokeGetClassName();
		InvokeGetRemark();

		bool setReloadRequired = false;
		
		{
			Lock variableGuard(_variableListMutex);
			for each (AxVariable^ element in _variableList)
			{
				if (!element->SpsIdChanged())
				{
					setReloadRequired = true;
					break;
				}
			}
		}

		{
			Lock variableGuard(_variableListMutex);
			void* handle = GetRawHandle();
			if (handle)
			{
				AX_VAR_DSC data = 0;
				while (data = AxVarDscFromInstance(handle, data))
				{
					String^ name = gcnew String(AxGetNameFromVarDSC(data));
					if (name->Length == 0) continue;
					if (!_variables->ContainsKey(name))
					{
						setReloadRequired = true;
						break;
					}
				}
			}
			else
			{
				SetCleanUp();
				return false;
			}
		}

		if (setReloadRequired)
		{
			SetReloadRequired();
			return false;
		}

		{
			Lock subinstanceGuard(_subinstanceListMutex);
			for each (AxInstance^ element in _subinstanceList)
			{
				if (!element->SpsIdChanged())
				{
					setReloadRequired = true;
					break;
				}
			}
		}

		if (setReloadRequired)
		{
			SetReloadRequired();
			return false;
		}

		return true;
	}

	void* AxInstance::GetRawHandle()
	{
		char* cName = _converter.GetCString(_name);
		void* handle = nullptr;
		if (_parent)
		{
			handle = _parent->GetRawHandle();
			if (handle) handle = AxQueryInstanceFromParent(handle, cName);
		}
		else handle = AxQueryInstance(cName);

		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		return handle;
	}

	//{{{ Queued init methods
	void AxInstance::InvokeGetClassName()
	{
		_className = "";
		void* handle = GetRawHandle();
		if (!handle) return;
		const char* result = AxGetInstanceClassPath(handle);
		if (!result) return;
		String^ value = gcnew String(result);
		Int32 startIndex = value->LastIndexOf('/');
		if (startIndex < 0) return;
		startIndex++;
		if (startIndex >= value->Length) return;
		Int32 stopIndex = value->LastIndexOf('.');
		if (stopIndex < 0 || stopIndex < startIndex) return;
		_className = value->Substring(startIndex, stopIndex - startIndex);
	}

	void AxInstance::GetClassName()
	{
		_ax->QueueInitFunction(Binder::Bind(gcnew NoParameterDelegate(this, &AxInstance::InvokeGetClassName)));
	}

	void AxInstance::InvokeGetRemark()
	{
		void* handle = GetRawHandle();
		if (!handle) return;
		const char* result = AxGetInstanceRemark(handle);
		if (!result) return;
		_remark = gcnew String(result);
	}

	void AxInstance::GetRemark()
	{
		_ax->QueueInitFunction(Binder::Bind(gcnew NoParameterDelegate(this, &AxInstance::InvokeGetRemark)));
	}

	void AxInstance::InvokeGetVariables()
	{
		Lock variableGuard(_variableListMutex);
		_variables->Clear();
		_variableList->Clear();
		void* handle = GetRawHandle();
		if (!handle) return;
		AX_VAR_DSC data = 0;
		while (data = AxVarDscFromInstance(handle, data))
		{
			String^ name = gcnew String(AxGetNameFromVarDSC(data));
			if (name->Length == 0) continue;
			AxVariable^ variable;
			try
			{
				variable = gcnew AxVariable(this, name);
			}
			catch (const AxVariableTypeException^) { continue; }
			catch (const Exception^) { continue; }
			_variables->Add(name, variable);
			_variableList->Add(variable);
			variable->ValueChanged += _variableValueChangedDelegate;
			variable->ArrayValueChanged += _arrayValueChangedDelegate;
		}
	}

	void AxInstance::InvokeGetSubinstances(GetSubinstancesData^ data)
	{
		Lock subinstanceGuard(_subinstanceListMutex);
		_subinstances->Clear();
		_subinstanceList->Clear();
		void* handle = GetRawHandle();
		if (!handle) return;
		AxSubInstanceList_StructPt pInstanceList = nullptr;
		data->InstanceCount = AxGetSubInstanceList(handle, &pInstanceList);
		if (data->InstanceCount == 0) return;
		data->PInstanceList = pInstanceList;
	}

	AxInstance::GetSubinstancesData^ AxInstance::GetVariablesAndSubinstances()
	{
		_ax->QueueInitFunction(Binder::Bind(gcnew NoParameterDelegate(this, &AxInstance::InvokeGetVariables)));

		GetSubinstancesData^ data = gcnew GetSubinstancesData();
		_ax->QueueInitFunction(Binder::Bind(gcnew GetSubinstancesDelegate(this, &AxInstance::InvokeGetSubinstances), data));

		return data;
	}

	void AxInstance::InvokeInitFinished(ManualResetEvent^ resetEvent, GetSubinstancesData^ data)
	{
		ResetEventLock resetEventGuard(resetEvent);
		{
			Lock variableGuard(_variableListMutex);
			for each (AxVariable^ variable in _variableList)
			{
				variable->ReloadStaticProperties(false);
			}
		}

		for (UInt32 i = 0; i < data->InstanceCount; i++)
		{
			String^ name = gcnew String(data->PInstanceList[i].instancePath);
			if (name->Length == 0 || name->LastIndexOf('.') == -1) continue;
			name = name->Substring(name->LastIndexOf('.') + 1);
			AxInstance^ instance;
			instance = gcnew AxInstance(_ax, this, name);
			_subinstances->Add(name, instance);
			_subinstanceList->Add(instance);
		}
		data->CleanUp();
		_initComplete = true;
	}

	void AxInstance::InitFinished(GetSubinstancesData^ data, bool wait)
	{
		_initResetEvent->Reset();
		_ax->QueueInitFunction(Binder::Bind(gcnew InitFinishedDelegate(this, &AxInstance::InvokeInitFinished), _initResetEvent, data));
		if (wait) _initResetEvent->WaitOne();
	}
	//}}}

	void AxInstance::WaitForInitCompleted()
	{
		if(!_initComplete) _initResetEvent->WaitOne();
		if (_variableList->Count > 0 && !_variableList[_variableList->Count - 1]->ReloadComplete) _variableList[_variableList->Count - 1]->WaitForReloadCompleted();
	}

	bool AxInstance::ReloadStaticProperties(bool wait)
	{
		GetClassName();
		GetRemark();
		GetSubinstancesData^ data = GetVariablesAndSubinstances();
		InitFinished(data, wait);
		if (wait)
		{
			if (_variableList->Count > 0 && !_variableList[_variableList->Count - 1]->ReloadComplete) _variableList[_variableList->Count - 1]->WaitForReloadCompleted();
			return _className != ""; //_className is empty if handle could not be created
		}
		else
		{
			void* handle = GetRawHandle();
			return handle != nullptr;
		}
	}

	AxVariable^ AxInstance::Get(String^ variableName)
	{
		Lock variableGuard(_variableListMutex);
		if (_variables->ContainsKey(variableName)) return _variables[variableName];
		return nullptr;
	}

	AxInstance^ AxInstance::GetSubinstance(String^ instanceName)
	{
		Lock subinstanceGuard(_subinstanceListMutex);
		if (_subinstances->ContainsKey(instanceName)) return _subinstances[instanceName];
		return nullptr;
	}

	bool AxInstance::VariableExists(String^ variableName)
	{
		Lock variableGuard(_variableListMutex);
		return _variables->ContainsKey(variableName);
	}

	bool AxInstance::SubinstanceExists(String^ instanceName)
	{
		Lock subinstanceGuard(_subinstanceListMutex);
		return _subinstances->ContainsKey(instanceName);
	}

	void AxInstance::OnValueChanged(AxVariable ^sender, AxVariableValue^ value, DateTime timestamp)
	{
		VariableValueChanged(sender, value, timestamp);
	}

	void AxInstance::OnArrayValueChanged(AxVariable ^sender, UInt16 index, AxVariableValue^ value, DateTime timestamp)
	{
		ArrayValueChanged(sender, index, value, timestamp);
	}
}