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
}