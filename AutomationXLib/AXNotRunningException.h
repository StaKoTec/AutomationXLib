#pragma once

#include "AXException.h"

namespace AutomationX
{
	ref class AXNotRunningException : public AXException
	{
	public:
		AXNotRunningException();
		AXNotRunningException(String^ message);
	};
}

