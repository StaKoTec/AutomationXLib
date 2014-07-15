#include "stdafx.h"
#include "AXException.h"

namespace AutomationX
{
	AXException::AXException() : System::Exception()
	{
	}

	AXException::AXException(String^ message) : System::Exception(message)
	{
	}

	AXNotRunningException::AXNotRunningException() : AXException()
	{
	}

	AXNotRunningException::AXNotRunningException(String^ message) : AXException(message)
	{
	}

	AXInstanceException::AXInstanceException() : AXException()
	{
	}

	AXInstanceException::AXInstanceException(String^ message) : AXException(message)
	{
	}

	AXVariableException::AXVariableException() : AXInstanceException()
	{
	}

	AXVariableException::AXVariableException(String^ message) : AXInstanceException(message)
	{
	}

	AXVariableTypeException::AXVariableTypeException() : AXVariableException()
	{
	}

	AXVariableTypeException::AXVariableTypeException(String^ message) : AXVariableException(message)
	{
	}

	AXArrayIndexOutOfRangeException::AXArrayIndexOutOfRangeException() : AXVariableException()
	{
	}

	AXArrayIndexOutOfRangeException::AXArrayIndexOutOfRangeException(String^ message) : AXVariableException(message)
	{
	}
}