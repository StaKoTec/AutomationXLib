#include "stdafx.h"
#include "AXNotRunningException.h"

namespace AutomationX
{
	AXNotRunningException::AXNotRunningException() : AXException()
	{
	}

	AXNotRunningException::AXNotRunningException(String^ message) : AXException(message)
	{
	}
}