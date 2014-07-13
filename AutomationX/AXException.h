#pragma once

using namespace System;

namespace AutomationX
{
	ref class AXException : public System::Exception
	{
	public:
		AXException();
		AXException(String^ message);
	};

}