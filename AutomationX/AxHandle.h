#pragma once

using namespace System;

namespace AutomationX
{
	public ref class AxHandle
	{
	private:
		void* _handle = nullptr;
	public:
		property void* Raw { void* get() { return _handle; }; void set(void* value) { _handle = value; }; }
		property bool Valid { bool get() { return _handle != 0; }; }

		AxHandle();
		AxHandle(void* handle);
	};
}

