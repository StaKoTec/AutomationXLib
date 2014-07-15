// AutomationXLib.h

#pragma once

using namespace System;

#include "ManagedTypeConverter.h"

namespace AutomationX
{
	public ref class AX
	{
	private:
		ManagedTypeConverter _converter;
		Timers::Timer^ _workerTimer;

		void OnWorkerTimerElapsed(System::Object ^sender, System::Timers::ElapsedEventArgs ^e);
	public:
		delegate void ShutdownEventHandler(AX^ sender);

		/// <summary>Fired when aX is shutting down.</summary>
		event ShutdownEventHandler^ OnShutdown;

		/// <summary>Checks if aX is running and if the local computer is running as the master of a redundant master slave server configuration.</summary>
		/// <returns>true when aX is running, otherwise false.</returns>
		property bool Connected { bool get(); }

		/// <summary>Constructor</summary>
		AX();
		
		/// <summary>Checks if aX is running and throws AXNotRunningException if not.</summary>
		/// <exception cref="AXNotRunningException">Thrown when aX is not running.</exception>
		void CheckRunning();

		/// <summary>Tell aX to shut down.</summary>
		void Shutdown();

		/// <summary>Returns all instance names of the specified class.</summary>
		System::Collections::Generic::List<String^>^ GetInstanceNames(String^ className);
	};
}
