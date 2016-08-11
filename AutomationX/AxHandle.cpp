#include "stdafx.h"
#include "AxHandle.h"

namespace AutomationX
{
	AxHandle::AxHandle()
	{
	}

	AxHandle::AxHandle(void* handle) : _handle(handle)
	{
	}
}