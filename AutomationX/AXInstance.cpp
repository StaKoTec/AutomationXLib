#include "stdafx.h"
#include "AXInstance.h"

namespace AutomationX
{
	String^ AXInstance::ClassName::get()
	{
		if (!HandleSpsIdChange()) return "";
		if (_className->Length > 0) return _className;
		void* handle = GetHandle();
		const char* result = AxGetInstanceClassPath(handle);
		if (!result) throw gcnew AXInstanceException("The instance handle is invalid.");
		String^ value = gcnew String(result);
		Int32 startIndex = value->LastIndexOf('/');
		if (startIndex < 0) return "";
		startIndex++;
		if (startIndex >= value->Length) return "";
		Int32 stopIndex = value->LastIndexOf('.');
		if (stopIndex < 0 || stopIndex < startIndex) return "";
		_className = value->Substring(startIndex, stopIndex - startIndex);
		return _className;
	}

	String^ AXInstance::Remark::get()
	{
		if (!HandleSpsIdChange()) return "";
		void* handle = GetHandle();
		String^ value = gcnew String(AxGetInstanceRemark(handle));
		return value;
	}

	Int32 AXInstance::PolledVariablesCount::get()
	{
		return _polledVariablesCount;
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
		if (!HandleSpsIdChange()) return;
		ThreadPool::QueueUserWorkItem(gcnew WaitCallback(this, &AXInstance::RaiseStatusEvent), value);
		if (_statusVariable == nullptr) return;
		_statusVariable->Set(value);
	}

	void AXInstance::Error::set(String^ value)
	{
		if (!HandleSpsIdChange()) return;
		ThreadPool::QueueUserWorkItem(gcnew WaitCallback(this, &AXInstance::RaiseErrorEvent), value);
		if (_alarmVariable == nullptr) return;
		_alarmVariable->Set(true);
		if (_alarmTextVariable == nullptr) return;
		_alarmTextVariable->Set(value);
	}

	array<AXVariable^>^ AXInstance::Variables::get()
	{
		if (!HandleSpsIdChange()) return nullptr;
		if (_variableList->Count == 0) GetVariables();

		array<AXVariable^>^ variables = nullptr;
		try
		{
			_variableListMutex.WaitOne();
			variables = gcnew array<AXVariable^>(_variableList->Count);
			_variableList->CopyTo(variables);
			_variableListMutex.ReleaseMutex();
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
		if (!HandleSpsIdChange()) return nullptr;
		if (_subinstanceList->Count == 0) GetSubinstances();

		array<AXInstance^>^ instances = nullptr;
		try
		{
			_subinstanceListMutex.WaitOne();
			instances = gcnew array<AXInstance^>(_subinstanceList->Count);
			_subinstanceList->CopyTo(instances);
			_subinstanceListMutex.ReleaseMutex();
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
		System::Diagnostics::Debug::WriteLine("C start " + name);
		if (!ax) throw gcnew AXInstanceException("AX object is nullptr.");
		_parent = parent;
		_ax = ax;
		_spsId = _ax->SpsId;
		if (name->Length == 0) throw gcnew AXInstanceException("Instance name is empty.");
		_name = name;
		GetHandle(); //Check if instance exists
		_spsIdChangedDelegate = gcnew AX::SpsIdChangedEventHandler(this, &AXInstance::OnSpsIdChanged);
		_variableValueChangedDelegate = gcnew AXVariable::ValueChangedEventHandler(this, &AXInstance::OnValueChanged);
		_arrayValueChangedDelegate = gcnew AXVariable::ArrayValueChangedEventHandler(this, &AXInstance::OnArrayValueChanged);
		_ax->SpsIdChanged += _spsIdChangedDelegate;
		System::Diagnostics::Debug::WriteLine("C ende " + name);
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
		System::Diagnostics::Debug::WriteLine("D start " + _name);
		_disposed = true;
		_stopWorkerThread = true;
		_workerThreadMutex.WaitOne();
		try
		{
			if (_workerThread && (_workerThread->ThreadState == ThreadState::Running || _workerThread->ThreadState == ThreadState::WaitSleepJoin)) _workerThread->Join();
		}
		catch (const Exception^)
		{
		}
		_workerThreadMutex.ReleaseMutex();

		if (_spsIdChangedDelegate) _ax->SpsIdChanged -= _spsIdChangedDelegate;
		_onSpsIdChangedMutex.WaitOne();
		_onSpsIdChangedMutex.ReleaseMutex();

		_variableListMutex.WaitOne();
		for each (AXVariable^ element in _variableList)
		{
			element->~AXVariable(); //Dispose all variables belonging to this object
		}
		_variableList->Clear();
		_variables->Clear();
		_variableListMutex.ReleaseMutex();
		_subinstanceListMutex.WaitOne();
		for each (AXInstance^ element in _subinstanceList)
		{
			element->~AXInstance(); //Dispose all subinstances belonging to this object
		}
		_subinstanceList->Clear();
		_subinstances->Clear();
		_subinstanceListMutex.ReleaseMutex();
		_ax = nullptr;
		//GC::Collect(); //Uncomment to check for memory leaks

		System::Diagnostics::Debug::WriteLine("D ende " + _name);
	}

	void AXInstance::RaiseStatusEvent(Object^ statusText)
	{
		try
		{
			StatusEvent(this, (String^)statusText);
		}
		catch (Exception^ ex)
		{
			System::Diagnostics::Debug::WriteLine(ex->Message + " " + ex->StackTrace);
		}
	}

	void AXInstance::RaiseErrorEvent(Object^ errorText)
	{
		try
		{
			ErrorEvent(this, (String^)errorText);
		}
		catch (Exception^ ex)
		{
			System::Diagnostics::Debug::WriteLine(ex->Message + " " + ex->StackTrace);
		}
	}

	bool AXInstance::HandleSpsIdChange()
	{
		if (_disposed || !_ax) return false;
		if (_spsId != _ax->CheckSpsId())
		{
			char* cName = _converter.GetCString(_name);
			void* handle = _parent ? AxQueryInstanceFromParent(_parent->GetHandle(), cName) : AxQueryInstance(cName);
			Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
			if (!handle) return false;
			_spsId = _ax->SpsId;
		}
		return true;
	}

	void AXInstance::SetVariableEvents(bool value)
	{
		array<AXVariable^>^ variables = Variables;
		//We can't loop through _variableList as locking the mutex would cause a deadlock
		for each(AXVariable^ variable in variables)
		{
			variable->Events = value;
		}
	}
	
	void AXInstance::RegisterVariableToPoll(AXVariable^ variable)
	{
		_onSpsIdChangedMutex.WaitOne();
		try
		{
			
			_variablesToPollMutex.WaitOne();
			if (!_variablesToPoll->ContainsKey(variable->Name))
			{
				_variablesToPoll->Add(variable->Name, variable);
				_polledVariablesCount += (variable->IsArray) ? variable->Length : 1;
			}
			_variablesToPollMutex.ReleaseMutex();
		}
		catch (const Exception^ ex)
		{
			_variablesToPollMutex.ReleaseMutex();
			_onSpsIdChangedMutex.ReleaseMutex();
			throw ex;
		}
		if (_stopWorkerThread)
		{
			try
			{
				if (_spsIdIsChanging)
				{
					_stopWorkerThread = false;
					_onSpsIdChangedMutex.ReleaseMutex();
					return;
				}
				_workerThreadMutex.WaitOne();
				_stopWorkerThread = true;
				while (_workerThread && _workerThread->ThreadState == ThreadState::Unstarted) Thread::Sleep(10);
				if (_workerThread && (_workerThread->ThreadState == ThreadState::Running || _workerThread->ThreadState == ThreadState::WaitSleepJoin)) _workerThread->Join();
				_stopWorkerThread = false;
				_workerThread = gcnew Thread(gcnew ThreadStart(this, &AXInstance::Worker));
				_workerThread->Priority = ThreadPriority::Highest;
				_workerThread->Start();
				_workerThreadMutex.ReleaseMutex();
			}
			catch (const Exception^ ex)
			{
				_workerThreadMutex.ReleaseMutex();
				_onSpsIdChangedMutex.ReleaseMutex();
				throw ex;
			}
		}
		_onSpsIdChangedMutex.ReleaseMutex();
	}

	void AXInstance::UnregisterVariableToPoll(AXVariable^ variable)
	{
		_onSpsIdChangedMutex.WaitOne();
		bool empty = false;
		try
		{
			_variablesToPollMutex.WaitOne();
			if (_variablesToPoll->ContainsKey(variable->Name)) _variablesToPoll->Remove(variable->Name);
			if (_variablesToPoll->Count == 0) empty = true;
			_polledVariablesCount -= (variable->IsArray) ? variable->Length : 1;
			_variablesToPollMutex.ReleaseMutex();
		}
		catch (const Exception^ ex)
		{
			_variablesToPollMutex.ReleaseMutex();
			_onSpsIdChangedMutex.ReleaseMutex();
			throw ex;
		}
		if (_spsIdIsChanging)
		{
			_stopWorkerThread = true;
			_onSpsIdChangedMutex.ReleaseMutex();
			return;
		}
		try
		{
			_workerThreadMutex.WaitOne();
			if (empty)
			{
				_stopWorkerThread = true;
				while (_workerThread && _workerThread->ThreadState == ThreadState::Unstarted) Thread::Sleep(10);
				if (_workerThread && (_workerThread->ThreadState == ThreadState::Running || _workerThread->ThreadState == ThreadState::WaitSleepJoin)) _workerThread->Join();
			}
			_workerThreadMutex.ReleaseMutex();
		}
		catch (const Exception^ ex)
		{
			_workerThreadMutex.ReleaseMutex();
			_onSpsIdChangedMutex.ReleaseMutex();
			throw ex;
		}
		_onSpsIdChangedMutex.ReleaseMutex();
	}

	void AXInstance::Worker()
	{
		try
		{
			DateTime time;
			Int32 timeToSleep = 0;
			while (!_stopWorkerThread)
			{
				time = DateTime::Now;
				if (!HandleSpsIdChange()) return;
				try
				{
					_variablesToPollMutex.WaitOne();
					for each (KeyValuePair<String^, AXVariable^> pair in _variablesToPoll)
					{
						if (_stopWorkerThread)
						{
							_variablesToPollMutex.ReleaseMutex();
							return;
						}
						pair.Value->Refresh(true);
					}
					_variablesToPollMutex.ReleaseMutex();
				}
				catch (Exception^ ex)
				{
					_variablesToPollMutex.ReleaseMutex();
					System::Diagnostics::Debug::WriteLine(ex->Message + "\r\n" + ex->StackTrace);
				}
				if (_stopWorkerThread) return;
				timeToSleep = _pollingInterval - (Int32)DateTime::Now.Subtract(time).TotalMilliseconds;
				if (timeToSleep < 1) timeToSleep = 1;
				Threading::Thread::Sleep(timeToSleep);
			}
		}
		catch (Exception^ ex)
		{
			System::Diagnostics::Debug::WriteLine(ex->Message + "\r\n" + ex->StackTrace);
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
			_variableListMutex.WaitOne();
			_variableList->Clear();
			if (!HandleSpsIdChange()) return;
			void* handle = GetHandle();
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
				try
				{
					_variablesToPollMutex.WaitOne();
					for each (String^ element in elementsToRemove)
					{
						_variables->Remove(element);
						if (_variablesToPoll->ContainsKey(element))
						{
							_polledVariablesCount -= (_variablesToPoll[element]->IsArray) ? _variablesToPoll[element]->Length : 1;
							_variablesToPoll->Remove(element);
						}
					}
					_variablesToPollMutex.ReleaseMutex();
				}
				catch (const Exception^ ex)
				{
					_variablesToPollMutex.ReleaseMutex();
					_variableListMutex.ReleaseMutex();
					throw ex;
				}
			}
			_variableListMutex.ReleaseMutex();
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
			_subinstanceListMutex.WaitOne();
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
		if(!HandleSpsIdChange()) return nullptr;
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
		if(!HandleSpsIdChange()) return nullptr;
		if (_subinstances->Count == 0) GetSubinstances();
		if (_subinstances->ContainsKey(instanceName)) return _subinstances[instanceName];
		return nullptr;
	}

	bool AXInstance::VariableExists(String^ variableName)
	{
		if(!HandleSpsIdChange()) return false;
		char* cName = _converter.GetCString(Path + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) return false;
		AxFreeExecData(handle);
		return true;
	}

	bool AXInstance::SubinstanceExists(String^ instanceName)
	{
		if(!HandleSpsIdChange()) return false;
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
		if (_disposed) return;
		_onSpsIdChangedMutex.WaitOne();
		try
		{
			if (_disposed)
			{
				_onSpsIdChangedMutex.ReleaseMutex();
				return;
			}
			_spsIdIsChanging = true;
			bool restartWorkerTimer = !_stopWorkerThread;
			_stopWorkerThread = true;
			try
			{
				_workerThreadMutex.WaitOne();
				if (!_stopWorkerThread) restartWorkerTimer = true;
				_stopWorkerThread = true;
				while (_workerThread && _workerThread->ThreadState == ThreadState::Unstarted) Thread::Sleep(10);
				if (_workerThread && (_workerThread->ThreadState == ThreadState::Running || _workerThread->ThreadState == ThreadState::WaitSleepJoin)) _workerThread->Join();
				_workerThreadMutex.ReleaseMutex();
			}
			catch (const Exception^)
			{
				_workerThreadMutex.ReleaseMutex();
			}
			try
			{
				GetVariables();
				GetSubinstances();
			}
			catch (const Exception^ ex)
			{
				_spsIdIsChanging = false;
				_onSpsIdChangedMutex.ReleaseMutex();
				throw ex;
			}
			if (restartWorkerTimer || !_stopWorkerThread)
			{
				try
				{
					_workerThreadMutex.WaitOne();
					_stopWorkerThread = true;
					while (_workerThread && _workerThread->ThreadState == ThreadState::Unstarted) Thread::Sleep(10);
					if (_workerThread && (_workerThread->ThreadState == ThreadState::Running || _workerThread->ThreadState == ThreadState::WaitSleepJoin)) _workerThread->Join();
					_stopWorkerThread = false;
					_workerThread = gcnew Thread(gcnew ThreadStart(this, &AXInstance::Worker));
					_workerThread->Priority = ThreadPriority::Highest;
					_workerThread->Start();
					_workerThreadMutex.ReleaseMutex();
				}
				catch (const Exception^ ex)
				{
					_workerThreadMutex.ReleaseMutex();
					_onSpsIdChangedMutex.ReleaseMutex();
					_spsIdIsChanging = false;
					throw ex;
				}
			}
			_spsIdIsChanging = false;
		}
		catch (const Exception^ ex)
		{
			_onSpsIdChangedMutex.ReleaseMutex();
			throw ex;
		}
		_onSpsIdChangedMutex.ReleaseMutex();
	}
}
