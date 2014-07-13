#include "stdafx.h"
#include "ManagedTypeConverter.h"

namespace AutomationX
{
	ManagedTypeConverter::ManagedTypeConverter()
	{
	}

	std::string ManagedTypeConverter::GetString(String^ s)
	{
		const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		std::string os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
		return os;
	}

	String^ ManagedTypeConverter::GetString(std::string& s)
	{
		return gcnew String(s.c_str());
	}

	char* ManagedTypeConverter::GetCString(String^ s)
	{
		char* chars = (char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		return chars;
	}
}