// This is the main DLL file.

#include "stdafx.h"

#include "Ax.h"

namespace AutomationX
{
	bool Ax::Connected::get()
	{ 
		return AxIsRunning() && AxIsHostMaster();
	}

	Ax::Ax(UInt32 eventThreadCount)
	{
		if (eventThreadCount > 500) eventThreadCount = 500;
		else if (eventThreadCount < 1) eventThreadCount = 1;
		_eventThreadCount = eventThreadCount;

		AxInit(); //First function to call
		//AxOmAttachToObjectMemory must be called after AxInit
		if (!AxOmAttachToObjectMemory()) throw gcnew AxException("Could not attach to shared memory. Make sure AutomationX is running and the user running this program has enough privileges.");
		AxOmQueryProcessGroupInfo(); //No interpretable return value, must be called after AxOmAttachToObjectMemory
		_spsId = new int;
		AxHasSpsIdChanged(_spsId);
		_stopEventThreads = false;
		_stopWorkerThread = false;
		_workerThread = gcnew Thread(gcnew ThreadStart(this, &Ax::Worker));
		_workerThread->Priority = ThreadPriority::Highest;
		_workerThread->Start();

		for (UInt32 i = 0; i < eventThreadCount; i++)
		{
			Thread^ eventThread = gcnew Thread(gcnew ThreadStart(this, &Ax::EventWorker));
			eventThread->Priority = ThreadPriority::AboveNormal;
			eventThread->Start();
			_eventThreads->Add(eventThread);
		}
	}

	Ax::~Ax()
	{
		this->!Ax();
	}

	Ax::!Ax()
	{
		if (_spsIdChangedThread) _spsIdChangedThread->Join();
		_stopEventThreads = true;
		_stopWorkerThread = true;
		if(_workerThread) _workerThread->Join();
		for (Int32 i = 0; i < _eventThreads->Count; i++)
		{
			_eventThreads[i]->Join();
		}
		if (_spsId)
		{
			delete _spsId;
			_spsId = nullptr;
		}
	}

	void Ax::QueueInitFunction(System::Action^ function)
	{
		_initQueue.Enqueue(function);
	}

	void Ax::QueueSynchronousFunction(System::Action^ function)
	{
		_synchronousQueue.Enqueue(function);
	}

	//{{{ Queued methods
		void Ax::InvokeWriteJournal(int priority, String^ position, String^ message, String^ value, String^ fileName, DateTime time)
		{
			Double aXTime = AxConvertDataTime_ToValue(time.Year, time.Month, time.Day, time.Hour, time.Minute, time.Second, time.Millisecond);
			char* pPosition = _converter.GetCString(position);
			char* pMessage = _converter.GetCString(message);
			char* pValue = _converter.GetCString(value);
			char* pFileName = _converter.GetCString(fileName);
			AxLogTS(priority, pPosition, pMessage, pValue, pFileName, aXTime);
			Marshal::FreeHGlobal(IntPtr((void*)pPosition));
			Marshal::FreeHGlobal(IntPtr((void*)pMessage));
			Marshal::FreeHGlobal(IntPtr((void*)pValue));
			Marshal::FreeHGlobal(IntPtr((void*)pFileName));
		}

		void Ax::WriteJournal(int priority, String^ position, String^ message, String^ value, String^ fileName)
		{
			_synchronousQueue.Enqueue(Binder::Bind(gcnew WriteJournalDelegate(this, &Ax::InvokeWriteJournal), priority, position, message, value, fileName, DateTime::Now));
		}

		void Ax::WriteJournal(int priority, String^ position, String^ message, String^ value, String^ fileName, DateTime time)
		{
			_synchronousQueue.Enqueue(Binder::Bind(gcnew WriteJournalDelegate(this, &Ax::InvokeWriteJournal), priority, position, message, value, fileName, time));
		}

		void Ax::InvokeGetClassNames(ManualResetEvent^ resetEvent, List<String^>^ result)
		{
			ResetEventLock resetEventGuard(resetEvent);
			std::vector<char*> buffers(1);
			AxGetAllClasses(&buffers.at(0), 1);
			int numberOfClasses = AxGetNumberOfAllClasses();
			buffers.resize(numberOfClasses);
			int count = AxGetAllClasses(&buffers.at(0), numberOfClasses);
			for (int i = 0; i < count; i++)
			{
				String^ name = gcnew String(buffers.at(i));
				if (name->Length == 0) continue;
				result->Add(name);
			}
		}

		void Ax::InvokeGetInstanceNames(ManualResetEvent^ resetEvent, String^ className, List<String^>^ result)
		{
			ResetEventLock resetEventGuard(resetEvent);
			char* cName = _converter.GetCString(className);
			AX_INSTANCE data = nullptr;
			while (data = AxGetInstance(data, cName))
			{
				String^ instanceName = gcnew String(AxGetInstanceName(data));
				if (instanceName->Length == 0) continue;
				result->Add(instanceName);
			}
			Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		}

		System::Collections::Generic::List<String^>^ Ax::GetInstanceNames(String^ className)
		{
			List<String^>^ result = gcnew List<String^>();
			ManualResetEvent^ resetEvent = gcnew ManualResetEvent(false);
			QueueSynchronousFunction(Binder::Bind(gcnew GetInstanceNamesDelegate(this, &Ax::InvokeGetInstanceNames), resetEvent, className, result));
			resetEvent->WaitOne();
			return result;
		}

		System::Collections::Generic::List<String^>^ Ax::GetClassNames()
		{
			List<String^>^ result = gcnew List<String^>();
			ManualResetEvent^ resetEvent = gcnew ManualResetEvent(false);
			QueueSynchronousFunction(Binder::Bind(gcnew GetClassNamesDelegate(this, &Ax::InvokeGetClassNames), resetEvent, result));
			resetEvent->WaitOne();
			return result;
		}

		void Ax::InvokeAddVariableToPoll(UInt32 id, AxVariable^ value)
		{
			Lock variablesToPollGuard(_variablesToPollMutex);
			Lock variablesToAddGuard(_variablesToAddMutex);
			if (_variablesToAdd->Contains(id))
			{
				_variablesToPoll->Add(id, value);
				_variablesToPollCount += value->Length;
			}
		}

		UInt32 Ax::AddVariableToPoll(AxVariable^ value)
		{
			if (!value) return 0;
			UInt32 id = 0;
			{
				Lock variablesToPollIdGuard(_variablesToPollIdMutex);
				while (id == 0) id = _variablesToPollId++;
			}

			{
				Lock variablesToAddGuard(_variablesToAddMutex);
				_variablesToAdd->Add(id);
			}
			QueueInitFunction(Binder::Bind(gcnew AddVariableToPollDelegate(this, &Ax::InvokeAddVariableToPoll), id, value));
			
			return id;
		}

		/*void Ax::InvokeRemoveVariableToPoll(UInt32 id)
		{
			if (id == 0) return;
			if (_variablesToPoll->ContainsKey(id))
			{
				_variablesToPollCount -= _variablesToPoll[id]->Length;
				_variablesToPoll->Remove(id);
			}
		}*/

		void Ax::RemoveVariableToPoll(UInt32 id)
		{
			if (id == 0) return;
			Lock variablesToPollGuard(_variablesToPollMutex);
			{
				Lock variablesToAddGuard(_variablesToAddMutex);
				if (_variablesToAdd->Contains(id)) _variablesToAdd->Remove(id);
			}
			if (_variablesToPoll->ContainsKey(id))
			{
				_variablesToPollCount -= _variablesToPoll[id]->Length;
				_variablesToPoll->Remove(id);
			}
			//QueueInitFunction(Binder::Bind(gcnew RemoveVariableToPollDelegate(this, &Ax::InvokeRemoveVariableToPoll), id));
		}

		void Ax::AddVariableToPush(AxVariable^ value)
		{
			if (!value) return;

			{
				Lock variablesToPushGuard(_variablesToPushMutex);
				_variablesToPush->Add(value);
			}
		}
	//}}}

	UInt32 Ax::AddSpsIdChangedInstanceCallback(System::Action^ function)
	{
		UInt32 id = 0;
		{
			Lock spsIdChangedInstanceIdGuard(_spsIdChangedInstanceIdMutex);
			while (id == 0) id = _spsIdChangedInstanceId++;
		}
		Lock spsIdChangedInstanceCallbacksGuard(_spsIdChangedInstanceCallbacksMutex);
		_spsIdChangedInstanceCallbacks->Add(id, function);
		return id;
	}
	
	void Ax::RemoveSpsIdChangedInstanceCallback(UInt32 id)
	{
		if (id == 0) return;
		Lock spsIdChangedInstanceCallbacksGuard(_spsIdChangedInstanceCallbacksMutex);
		_spsIdChangedInstanceCallbacks->Remove(id);
	}

	bool Ax::SpsIdChanged()
	{
		return AxHasSpsIdChanged(_spsId) == 1;
	}

	void Ax::SpsIdChangedThread()
	{
		SpsIdChangedAfter(this);
	}

	void Ax::EventWorker()
	{
		while (!_stopEventThreads)
		{
			if(!_eventResetEvent->WaitOne(1000, false)) continue;
			while (!_eventQueue.IsEmpty && !_stopEventThreads)
			{
				try
				{
					AxVariableEventData^ eventData;
					if (_eventQueue.TryDequeue(eventData))
					{
						TimeSpan processingTime = DateTime::Now - eventData->Timestamp;
						if (processingTime.TotalSeconds >= 1) OnError(this, 3, "Event processing took " + processingTime.TotalSeconds.ToString("0.00") + " seconds.");
						if (eventData->Variable->IsArray) eventData->Variable->RaiseArrayValueChanged(eventData->Index, eventData->Value, eventData->Timestamp);
						else eventData->Variable->RaiseValueChanged(eventData->Value, eventData->Timestamp);
					}
				}
				catch (Exception^ ex)
				{
					OnError(this, 4, ex->Message + " " + ex->StackTrace);
				}
			}
		}
	}

	void Ax::Worker()
	{
		DateTime time;
		Int32 timeToSleep = 0;
		bool spsIdChanged = false;
		Action^ action;

		while (!_stopWorkerThread)
		{
			try
			{
				time = DateTime::Now;
				if (AxShutdownEvent() || !AxIsRunning())
				{
					ShuttingDown(this);
					break;
				}

				if (spsIdChanged)
				{
					spsIdChanged = false;
					SpsIdChangedBefore(this);
					array<System::Action^>^ callbacks = nullptr;
					{
						Lock spsIdChangedInstanceCallbacksGuard(_spsIdChangedInstanceCallbacksMutex);
						callbacks = gcnew array<System::Action^>(_spsIdChangedInstanceCallbacks->Values->Count);
						_spsIdChangedInstanceCallbacks->Values->CopyTo(callbacks, 0);
					}

					for each (System::Action^ callback in callbacks)
					{
						if (callback) callback();
					}

					if (_spsIdChangedThread) _spsIdChangedThread->Join();
					_spsIdChangedThread = gcnew Thread(gcnew ThreadStart(this, &Ax::SpsIdChangedThread));
					_spsIdChangedThread->Start();
				}

				while (_initQueue.Count > 0)
				{
					spsIdChanged = SpsIdChanged();
					if (spsIdChanged) break;

					if (_initQueue.TryDequeue(action) && action) action();
				}

				if (spsIdChanged) continue;

				array<AxVariable^>^ variablesToPush;
				{
					Lock variablesToPushGuard(_variablesToPushMutex);
					variablesToPush = _variablesToPush->ToArray();
					_variablesToPush->Clear();
				}
				for each(AxVariable^ variable in variablesToPush)
				{
					//Don't check for changed SPS ID here => changed might stay "true" in AxVariable destructor
					if (variable->Changed) variable->Push();
				}

				{
					Lock variablesToPollGuard(_variablesToPollMutex);
					for each (KeyValuePair<UInt32, AxVariable^>^ pair in _variablesToPoll)
					{
						spsIdChanged = SpsIdChanged();
						if (spsIdChanged) break;
						pair->Value->LockPullMutex();
						try
						{
							if (pair->Value->Changed)
							{
								pair->Value->Push();
							}
							else
							{
								List<UInt16>^ changedIndexes = pair->Value->Pull();
								if (changedIndexes->Count > 0)
								{
									for each (UInt16 index in changedIndexes)
									{
										if (_eventQueue.Count > 1000000)
										{
											OnError(this, 2, "Event queue full. Dropping variable changed events.");
											pair->Value->UnlockPullMutex();
											continue;
										}
										else if (_eventQueue.Count > 500000)
										{
											OnError(this, 1, "Event queue almost full.");
										}
										_eventQueue.Enqueue(gcnew AxVariableEventData(pair->Value, index, pair->Value->IsArray ? pair->Value->GetValue(index) : pair->Value->GetValue(), DateTime::Now));
									}
									_eventResetEvent->Set();
								}
							}
						}
						catch (Exception^ ex)
						{
							OnError(this, 5, ex->Message + " " + ex->StackTrace);
						}
						pair->Value->UnlockPullMutex();
					}
				}

				if (spsIdChanged) continue;

				for (Int32 i = 0; i < 100 && _synchronousQueue.Count > 0; i++)
				{
					spsIdChanged = SpsIdChanged();
					if (spsIdChanged) break;
					if (_synchronousQueue.TryDequeue(action) && action) action();
				}

				if (spsIdChanged) continue;

				if (_stopWorkerThread) return;

				_lastCycleTime = (Int32)DateTime::Now.Subtract(time).TotalMilliseconds;
				timeToSleep = _cycleTime - _lastCycleTime;
				if (timeToSleep > 0) Threading::Thread::Sleep(timeToSleep);
			}
			catch (Exception^ ex)
			{
				OnError(this, 5, ex->Message + " " + ex->StackTrace);
			}
		}
	}
}
