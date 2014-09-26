// AutomationXLib.h

#pragma once

using namespace System;

#include "ManagedTypeConverter.h"

namespace AutomationX
{
	public ref class AX
	{
	private:
		delegate void NoParameterDelegate();
		ManagedTypeConverter _converter;
		Timers::Timer^ _workerTimer;
		int* _spsId = nullptr;
		Int32 _spsIdChangedThreadCount = 0;

		void OnWorkerTimerElapsed(System::Object ^sender, System::Timers::ElapsedEventArgs ^e);
		void RaiseSpsIdChanged(Object^ stateInfo);
	public:
		delegate void ShutdownEventHandler(AX^ sender);
		delegate void SpsIdChangedEventHandler(AX^ sender);

		/// <summary>Fired when aX is shutting down.</summary>
		event ShutdownEventHandler^ ShuttingDown;

		/// <summary>Fired when the SPS ID has changed.</summary>
		event SpsIdChangedEventHandler^ SpsIdChanged;

		/// <summary>Checks if aX is running and if the local computer is running as the master of a redundant master slave server configuration.</summary>
		/// <returns>true when aX is running, otherwise false.</returns>
		property bool Connected { bool get(); }

		/// <summary>Returns the current SPS ID.</summary>
		/// <returns>The current SPS ID.</returns>
		property Int32 SpsId { Int32 get() { return *_spsId; } }

		/// <summary>Constructor</summary>
		AX();

		virtual ~AX();
		
		/// <summary>Checks if aX is running and throws AXNotRunningException if not.</summary>
		/// <exception cref="AXNotRunningException">Thrown when aX is not running.</exception>
		void CheckRunning();

		/// <summary>Tell aX to shut down.</summary>
		void Shutdown();

		/// <summary>Returns all instance names of the specified class.</summary>
		System::Collections::Generic::List<String^>^ GetInstanceNames(String^ className);

		/// <summary>Returns all Class names.</summary>
		System::Collections::Generic::List<String^>^ AX::GetClassNames();

		/// <summary>Returns the Classpath of the specified instance.</summary>
		System::String^ AX::GetClassPath(String^ instanceName);

		/// <summary>Checks if the SPS ID has changed since the last call and returns the new SPS ID.</summary>
		/// <returns>The new SPS ID.</returns>
		Int32 CheckSpsId();

		void WriteJournal(int priority, String^ position, String^ message, String^ value, String^ fileName);
		void WriteJournal(int priority, String^ position, String^ message, String^ value, String^ fileName, DateTime time);
	};
}
