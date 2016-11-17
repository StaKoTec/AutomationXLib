// AutomationXLib.h

#pragma once

using namespace System;
using namespace System::Threading;

#include "AxVariable.h"
#include "ManagedTypeConverter.h"

namespace AutomationX
{
	public ref class Ax : IDisposable
	{
	private:
		ManagedTypeConverter _converter;
		int* _spsId = nullptr;
		volatile bool _stopEventThreads = true;
		volatile bool _stopWorkerThread = true;
		System::Threading::Thread^ _spsIdChangedThread = nullptr;
		System::Threading::Thread^ _workerThread = nullptr;
		System::Collections::Generic::List<System::Threading::Thread^>^ _eventThreads = gcnew System::Collections::Generic::List<System::Threading::Thread^>();
		UInt32 _cycleTime = 20;
		UInt32 _lastCycleTime = 0;
		UInt32 _eventThreadCount = 20;
		AutoResetEvent^ _eventResetEvent = gcnew AutoResetEvent(false);
		System::Collections::Concurrent::ConcurrentQueue<Action^> _initQueue;
		System::Collections::Concurrent::ConcurrentQueue<Action^> _synchronousQueue;
		System::Collections::Concurrent::ConcurrentQueue<AxVariableEventData^> _eventQueue;
		UInt32 _variablesToPollCount = 0;
		Object^ _variablesToPollIdMutex = gcnew Object();
		UInt32 _variablesToPollId = 0;
		Object^ _variablesToPollMutex = gcnew Object();
		System::Collections::Generic::Dictionary<UInt32, AxVariable^>^ _variablesToPoll = gcnew System::Collections::Generic::Dictionary<UInt32, AxVariable^>();
		Object^ _variablesToAddMutex = gcnew Object();
		System::Collections::Generic::HashSet<UInt32>^ _variablesToAdd = gcnew System::Collections::Generic::HashSet<UInt32>();
		Object^ _spsIdChangedInstanceIdMutex = gcnew Object();
		UInt32 _spsIdChangedInstanceId = 0;
		Object^ _spsIdChangedInstanceCallbacksMutex = gcnew Object();
		System::Collections::Generic::Dictionary<UInt32, System::Action^>^ _spsIdChangedInstanceCallbacks = gcnew System::Collections::Generic::Dictionary<UInt32, System::Action^>();

		void Worker();
		void EventWorker();
		void SpsIdChangedThread();

		bool SpsIdChanged();
		

		//{{{ Queued methods
			delegate void WriteJournalDelegate(int priority, String^ position, String^ message, String^ value, String^ fileName, DateTime time);
			void InvokeWriteJournal(int priority, String^ position, String^ message, String^ value, String^ fileName, DateTime time);
			delegate void GetClassNamesDelegate(ManualResetEvent^ resetEvent, List<String^>^ result);
			void InvokeGetClassNames(ManualResetEvent^ resetEvent, List<String^>^ result);
			delegate void GetInstanceNamesDelegate(ManualResetEvent^ resetEvent, String^ className, List<String^>^ result);
			void InvokeGetInstanceNames(ManualResetEvent^ resetEvent, String^ className, List<String^>^ result);
			delegate void AddVariableToPollDelegate(UInt32 id, AxVariable^ value);
			void InvokeAddVariableToPoll(UInt32 id, AxVariable^ value);
			//delegate void RemoveVariableToPollDelegate(UInt32 id);
			//void InvokeRemoveVariableToPoll(UInt32 id);
		//}}}
	internal:
		void QueueInitFunction(System::Action^ function);
		void QueueSynchronousFunction(System::Action^ function);

		UInt32 AddVariableToPoll(AxVariable^ value);
		void RemoveVariableToPoll(UInt32 id);

		UInt32 AddSpsIdChangedInstanceCallback(System::Action^ function);
		void RemoveSpsIdChangedInstanceCallback(UInt32 id);
	public:
		delegate void ErrorEventHandler(Ax^ sender, UInt32 errorId, String^ errorMessage);
		delegate void ShutdownEventHandler(Ax^ sender);
		delegate void SpsIdChangedEventHandler(Ax^ sender);

		/// <summary>Fired when errors occur.</summary>
		event ErrorEventHandler^ OnError;

		/// <summary>Fired when aX is shutting down.</summary>
		event ShutdownEventHandler^ ShuttingDown;

		/// <summary>Fired when the SPS ID was changed before any action is taken. Be very careful doing anything within the event handler. Don't interact with any aX objects as this might cause a deadlock!!!</summary>
		event SpsIdChangedEventHandler^ SpsIdChangedBefore;

		/// <summary>Fired when the SPS ID was changed after all instances and variables have been reloaded and checked for existance.</summary>
		event SpsIdChangedEventHandler^ SpsIdChangedAfter;

		/// <summary>Checks if aX is running and if the local computer is running as the master of a redundant master slave server configuration.</summary>
		/// <returns>true when aX is running, otherwise false.</returns>
		property bool Connected { bool get(); }

		property UInt32 VariablesToPollCount { UInt32 get() { return _variablesToPollCount; }; }
		property UInt32 EventThreadCount { UInt32 get() { return _eventThreadCount; }; }
		property UInt32 CycleTime { UInt32 get() { return _cycleTime; }; void set(UInt32 value) { _cycleTime = value; }; }
		property UInt32 LastCycleTime { UInt32 get() { return _lastCycleTime; }; }

		/// <summary>Returns the current SPS ID.</summary>
		/// <returns>The current SPS ID.</returns>
		property Int32 SpsId { Int32 get() { return *_spsId; } }

		/// <summary>Constructor</summary>
		/// <param name='eventThreadCount'>The number of event threads to start.</param>
		Ax(UInt32 eventThreadCount);

		virtual ~Ax();
		!Ax();

		void WriteJournal(int priority, String^ position, String^ message, String^ value, String^ fileName);
		void WriteJournal(int priority, String^ position, String^ message, String^ value, String^ fileName, DateTime time);

		System::Collections::Generic::List<String^>^ GetInstanceNames(String^ className);
		System::Collections::Generic::List<String^>^ GetClassNames();
	};
}
