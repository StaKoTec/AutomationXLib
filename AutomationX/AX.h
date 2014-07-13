// AutomationXLib.h

#pragma once

using namespace System;

#include "AXWriter.h"

namespace AutomationX
{
	public delegate void ShutdownEventHandler();
	public delegate void StatusEventHandler(String^ statusText);
	public delegate void ErrorEventHandler(String^ errorText);

	/// Class to read and write AutomationX variables.
	public ref class AX
	{
	private:
		String^ _instanceName;
		String^ _statusVariableName;
		String^ _alarmVariableName;
		AXWriter^ _writer;
		Timers::Timer^ _workerTimer;

		void OnWorkerTimerElapsed(System::Object ^sender, System::Timers::ElapsedEventArgs ^e);
	public:
		/// <summary>Fired when aX is shutting down.</summary>
		event ShutdownEventHandler^ OnShutdown;
		/// <summary>Fired when aX status variable provided with constructor is being set.</summary>
		event StatusEventHandler^ OnStatus;
		/// <summary>Fired when aX alarm variable provided with constructor is being set.</summary>
		event ErrorEventHandler^ OnError;

		AX(String^ instanceName);
		AX(String^ instanceName, String^ statusVariableName, String^ alarmVariableName);

		String^ GetInstanceName() { return _instanceName; }
		Boolean IsRunning();
		void CheckRunning();
		void SetStatus(String^ statusText);
		void SetError(String^ errorText);
		void Shutdown();
	};
}
