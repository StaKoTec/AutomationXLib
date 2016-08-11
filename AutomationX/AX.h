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
		System::Threading::Thread^ _workerThread = nullptr;
		System::Collections::Generic::List<System::Threading::Thread^>^ _eventThreads = gcnew System::Collections::Generic::List<System::Threading::Thread^>();
		UInt32 _cycleTime = 20;
		UInt32 _eventThreadCount = 20;
		AutoResetEvent^ _eventResetEvent = gcnew AutoResetEvent(false);
		System::Collections::Concurrent::ConcurrentQueue<Action^> _initQueue;
		System::Collections::Concurrent::ConcurrentQueue<Action^> _synchronousQueue;
		System::Collections::Concurrent::ConcurrentQueue<AxVariableEventData^> _eventQueue;
		Object^ _variablesToPollMutex = gcnew Object();
		System::Collections::Concurrent::ConcurrentDictionary<String^, AxVariable^>^ _variablesToPoll = gcnew System::Collections::Concurrent::ConcurrentDictionary<String^, AxVariable^>();

		void Worker();
		void EventWorker();
		bool SpsIdChanged();

		//{{{ Queueable methods
			delegate void WriteJournalDelegate(int priority, String^ position, String^ message, String^ value, String^ fileName, DateTime time);
			void InvokeWriteJournal(int priority, String^ position, String^ message, String^ value, String^ fileName, DateTime time);
		//}}}
	public:
		delegate void ShutdownEventHandler(Ax^ sender);

		/// <summary>Fired when aX is shutting down.</summary>
		event ShutdownEventHandler^ ShuttingDown;

		/// <summary>Checks if aX is running and if the local computer is running as the master of a redundant master slave server configuration.</summary>
		/// <returns>true when aX is running, otherwise false.</returns>
		property bool Connected { bool get(); }

		property UInt32 EventThreadCount { UInt32 get() { return _eventThreadCount; }; }
		property UInt32 CycleTime { UInt32 get() { return _cycleTime; }; void set(UInt32 value) { _cycleTime = value; }; }

		/// <summary>Returns the current SPS ID.</summary>
		/// <returns>The current SPS ID.</returns>
		property Int32 SpsId { Int32 get() { return *_spsId; } }

		/// <summary>Constructor</summary>
		/// <param name='eventThreadCount'>The number of event threads to start.</param>
		Ax(UInt32 eventThreadCount);

		virtual ~Ax();
		!Ax();

		void QueueInitFunction(System::Action^ function);
		void QueueSynchronousFunction(System::Action^ function);

		void WriteJournal(int priority, String^ position, String^ message, String^ value, String^ fileName);
		void WriteJournal(int priority, String^ position, String^ message, String^ value, String^ fileName, DateTime time);

		void AddVariableToPoll(AxVariable^ value);
		void RemoveVariableToPoll(AxVariable^ value);
	};
}
