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

	//{{{ Queueable methods
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
	//}}}

	void Ax::WriteJournal(int priority, String^ position, String^ message, String^ value, String^ fileName)
	{
		_synchronousQueue.Enqueue(Binder::Bind(gcnew WriteJournalDelegate(this, &Ax::InvokeWriteJournal), priority, position, message, value, fileName, DateTime::Now));
	}

	void Ax::WriteJournal(int priority, String^ position, String^ message, String^ value, String^ fileName, DateTime time)
	{
		_synchronousQueue.Enqueue(Binder::Bind(gcnew WriteJournalDelegate(this, &Ax::InvokeWriteJournal), priority, position, message, value, fileName, time));
	}

	void Ax::AddVariableToPoll(AxVariable^ value)
	{
		if (!value) return;
		Lock variablesToPollGuard(_variablesToPollMutex);
		_variablesToPoll->TryAdd(value->Path, value);
	}

	void Ax::RemoveVariableToPoll(AxVariable^ value)
	{
		if (!value) return;
		AxVariable^ returnedValue;
		Lock variablesToPollGuard(_variablesToPollMutex);
		_variablesToPoll->TryRemove(value->Path, returnedValue);
	}

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

			while (_initQueue.Count > 0)
			{
				spsIdChanged = SpsIdChanged();
				if (spsIdChanged) break;
				
				if (_initQueue.TryDequeue(action) && action) action();
			}
			
			if (spsIdChanged)
			{
				spsIdChanged = false;
				continue;
			}

			{
				Lock variablesToPollGuard(_variablesToPollMutex);
				for each (KeyValuePair<String^, AxVariable^>^ pair in _variablesToPoll)
				{
					if (pair->Value->Changed)
					{
						spsIdChanged = SpsIdChanged();
						if (spsIdChanged) break;
						pair->Value->Push();
					}
					else
					{
						List<UInt16>^ changedIndexes = pair->Value->Pull();
						for each (UInt16 index in changedIndexes)
						{
							_eventQueue.Enqueue(gcnew AxVariableEventData(pair->Value, index));
						}
						_eventResetEvent->Set();
					}
				}
			}

			if (spsIdChanged)
			{
				spsIdChanged = false;
				continue;
			}
			
			if (_synchronousQueue.Count > 0)
			{
				if(SpsIdChanged()) continue;
				if (_synchronousQueue.TryDequeue(action) && action) action();
			}
								
			if (_stopWorkerThread) return;
			timeToSleep = _cycleTime - (Int32)DateTime::Now.Subtract(time).TotalMilliseconds;
			if (timeToSleep < 1) timeToSleep = 1;
			Threading::Thread::Sleep(timeToSleep);
		}
	}
}
