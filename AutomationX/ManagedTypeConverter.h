#pragma once
#include <string>

using namespace System;
using namespace Runtime::InteropServices;

namespace AutomationX
{
	ref class ManagedTypeConverter
	{
	public:
		ManagedTypeConverter();
		std::string GetString(String^ s);
		String^ GetString(std::string& s);
		char* GetCString(String^ s);
	};
}

