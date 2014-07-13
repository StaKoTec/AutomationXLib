#pragma once

#include "AXException.h"

namespace AutomationX
{
	public ref class AXNotRunningException : public AXException
	{
	public:
		AXNotRunningException();
		AXNotRunningException(String^ message);
	};
}

