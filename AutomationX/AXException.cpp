#include "stdafx.h"
#include "AxException.h"

namespace AutomationX
{
	AxException::AxException() : System::Exception()
	{
	}

	AxException::AxException(String^ message) : System::Exception(message)
	{
	}

	AxNotRunningException::AxNotRunningException() : AxException()
	{
	}

	AxNotRunningException::AxNotRunningException(String^ message) : AxException(message)
	{
	}

	AxInstanceException::AxInstanceException() : AxException()
	{
	}

	AxInstanceException::AxInstanceException(String^ message) : AxException(message)
	{
	}

	AxVariableException::AxVariableException() : AxInstanceException()
	{
	}

	AxVariableException::AxVariableException(String^ message) : AxInstanceException(message)
	{
	}

	AxVariableReadOnlyException::AxVariableReadOnlyException() : AxVariableException()
	{
	}

	AxVariableReadOnlyException::AxVariableReadOnlyException(String^ message) : AxVariableException(message)
	{
	}

	AxVariableTypeException::AxVariableTypeException() : AxVariableException()
	{
	}

	AxVariableTypeException::AxVariableTypeException(String^ message) : AxVariableException(message)
	{
	}

	AxArrayIndexOutOfRangeException::AxArrayIndexOutOfRangeException() : AxVariableException()
	{
	}

	AxArrayIndexOutOfRangeException::AxArrayIndexOutOfRangeException(String^ message) : AxVariableException(message)
	{
	}
}