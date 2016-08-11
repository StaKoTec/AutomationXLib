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

	AxInstance::AxInstance(Ax^ ax, String^ name) : AxInstance(ax, nullptr, name)
	{
	}

	AxInstance::AxInstance(Ax^ ax, AxInstance^ parent, String^ name)
	{
		_ax = ax;
		_parent = parent;
		if (name->Length == 0) throw gcnew AxInstanceException("Instance name is empty.");
		_name = name;
		AxHandle^ handle = GetHandle(); //Check if instance exists
		if (!handle->Valid) throw gcnew AxInstanceException("Could not get instance handle for " + _name);
		_variableValueChangedDelegate = gcnew AxVariable::ValueChangedEventHandler(this, &AxInstance::OnValueChanged);
		_arrayValueChangedDelegate = gcnew AxVariable::ArrayValueChangedEventHandler(this, &AxInstance::OnArrayValueChanged);
		ReloadStaticProperties();
	}

	AxInstance::~AxInstance()
	{
		this->!AxInstance();
	}

	AxInstance::!AxInstance()
	{
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

	//{{{ Queueable methods
	void AxInstance::InvokeGetHandle(AxHandle^ handle, ManualResetEvent^ resetEvent)
	{
		ResetEventLock resetEventGuard(resetEvent);
		handle->Raw = GetRawHandle();
	}

	void AxInstance::InvokeGetClassName(ManualResetEvent^ resetEvent)
	{
		ResetEventLock resetEventGuard(resetEvent);
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
		ManualResetEvent^ resetEvent = gcnew ManualResetEvent(false);
		_ax->QueueInitFunction(Binder::Bind(gcnew NoParameterDelegate(this, &AxInstance::InvokeGetClassName), resetEvent));
		resetEvent->WaitOne();
	}

	void AxInstance::InvokeGetRemark(ManualResetEvent^ resetEvent)
	{
		ResetEventLock resetEventGuard(resetEvent);
		void* handle = GetRawHandle();
		if (!handle) return;
		const char* result = AxGetInstanceRemark(handle);
		if (!result) return;
		_remark = gcnew String(result);
	}

	void AxInstance::GetRemark()
	{
		ManualResetEvent^ resetEvent = gcnew ManualResetEvent(false);
		_ax->QueueInitFunction(Binder::Bind(gcnew NoParameterDelegate(this, &AxInstance::InvokeGetRemark), resetEvent));
		resetEvent->WaitOne();
	}

	void AxInstance::InvokeGetVariables(ManualResetEvent^ resetEvent)
	{
		ResetEventLock resetEventGuard(resetEvent);
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

	void AxInstance::GetVariables()
	{
		ManualResetEvent^ resetEvent = gcnew ManualResetEvent(false);
		_ax->QueueInitFunction(Binder::Bind(gcnew NoParameterDelegate(this, &AxInstance::InvokeGetVariables), resetEvent));
		resetEvent->WaitOne();
		Lock variableGuard(_variableListMutex);
		for each (AxVariable^ variable in _variableList)
		{
			variable->ReloadStaticProperties();
		}
	}

	void AxInstance::InvokeGetSubinstances(ManualResetEvent^ resetEvent, GetSubinstancesData^ data)
	{
		ResetEventLock resetEventGuard(resetEvent);
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

	void AxInstance::GetSubinstances()
	{
		ManualResetEvent^ resetEvent = gcnew ManualResetEvent(false);
		GetSubinstancesData^ data = gcnew GetSubinstancesData();
		_ax->QueueInitFunction(Binder::Bind(gcnew GetSubinstancesDelegate(this, &AxInstance::InvokeGetSubinstances), resetEvent, data));
		resetEvent->WaitOne();

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
	}
	//}}}

	AxHandle^ AxInstance::GetHandle()
	{
		AxHandle^ handle = gcnew AxHandle();
		ManualResetEvent^ resetEvent = gcnew ManualResetEvent(false);
		_ax->QueueInitFunction(Binder::Bind(gcnew GetHandleDelegate(this, &AxInstance::InvokeGetHandle), handle, resetEvent));
		resetEvent->WaitOne();
		return handle;
	}

	void AxInstance::ReloadStaticProperties()
	{
		GetClassName();
		GetRemark();
		GetVariables();
		GetSubinstances();
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

	void AxInstance::OnValueChanged(AxVariable ^sender)
	{
		VariableValueChanged(sender);
	}

	void AxInstance::OnArrayValueChanged(AxVariable ^sender, UInt16 index)
	{
		ArrayValueChanged(sender, index);
	}
}