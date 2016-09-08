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
			_variablesToPoll->Add(id, value);
			_variablesToPollCount += value->Length;
		}

		UInt32 Ax::AddVariableToPoll(AxVariable^ value)
		{
			if (!value) return 0;
			UInt32 id = 0;
			{
				Lock variablesToPollIdGuard(_variablesToPollIdMutex);
				while (id == 0) id = _variablesToPollId++;
			}

			QueueInitFunction(Binder::Bind(gcnew AddVariableToPollDelegate(this, &Ax::InvokeAddVariableToPoll), id, value));
			
			return id;
		}

		void Ax::InvokeRemoveVariableToPoll(UInt32 id)
		{
			if (id == 0) return;
			if (_variablesToPoll->ContainsKey(id))
			{
				_variablesToPollCount -= _variablesToPoll[id]->Length;
				_variablesToPoll->Remove(id);
			}
		}

		void Ax::RemoveVariableToPoll(UInt32 id)
		{
			QueueInitFunction(Binder::Bind(gcnew RemoveVariableToPollDelegate(this, &Ax::InvokeRemoveVariableToPoll), id));
		}
	//}}}

	bool Ax::SpsIdChanged()
	{
		return AxHasSpsIdChanged(_spsId) == 1;
	}

	void Ax::EventWorker()
	{
		while (!_stopEventThreads)
		{
			if(!_eventResetEvent->WaitOne(1000, false)) continue;
			while (_eventQueue.Count > 0 && !_stopEventThreads)
			{
				AxVariableEventData^ eventData;
				if (_eventQueue.TryDequeue(eventData))
				{
					if (eventData->Variable->IsArray) eventData->Variable->RaiseArrayValueChanged(eventData->Index);
					else eventData->Variable->RaiseValueChanged();
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
			time = DateTime::Now;
			if (AxShutdownEvent() || !AxIsRunning())
			{
				ShuttingDown(this);
				break;
			}

			if (spsIdChanged)
			{
				//Handle spsIdChanged
				spsIdChanged = false;
			}

			while (_initQueue.Count > 0)
			{
				spsIdChanged = SpsIdChanged();
				if (spsIdChanged) break;
				
				if (_initQueue.TryDequeue(action) && action) action();
			}
			
			if (spsIdChanged) continue;

			for each (KeyValuePair<UInt32, AxVariable^>^ pair in _variablesToPoll)
			{
				spsIdChanged = SpsIdChanged();
				if (spsIdChanged) break;
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
							_eventQueue.Enqueue(gcnew AxVariableEventData(pair->Value, index));
						}
						_eventResetEvent->Set();
					}
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
	}
}
