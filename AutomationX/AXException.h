#pragma once

using namespace System;

namespace AutomationX
{
	public ref class AXException : public System::Exception
	{
	public:
		AXException();
		AXException(String^ message);
	};

}