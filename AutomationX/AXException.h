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

	public ref class AXNotRunningException : public AXException
	{
	public:
		AXNotRunningException();
		AXNotRunningException(String^ message);
	};

	public ref class AXInstanceException : public AXException
	{
	public:
		AXInstanceException();
		AXInstanceException(String^ message);
	};

	public ref class AXVariableException : public AXInstanceException
	{
	public:
		AXVariableException();
		AXVariableException(String^ message);
	};

	public ref class AXVariableReadOnlyException : public AXVariableException
	{
	public:
		AXVariableReadOnlyException();
		AXVariableReadOnlyException(String^ message);
	};

	public ref class AXVariableTypeException : public AXVariableException
	{
	public:
		AXVariableTypeException();
		AXVariableTypeException(String^ message);
	};

	public ref class AXArrayIndexOutOfRangeException : public AXVariableException
	{
	public:
		AXArrayIndexOutOfRangeException();
		AXArrayIndexOutOfRangeException(String^ message);
	};
}