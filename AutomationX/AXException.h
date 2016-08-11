#pragma once

using namespace System;

namespace AutomationX
{
	public ref class AxException : public System::Exception
	{
	public:
		AxException();
		AxException(String^ message);
	};

	public ref class AxNotRunningException : public AxException
	{
	public:
		AxNotRunningException();
		AxNotRunningException(String^ message);
	};

	public ref class AxInstanceException : public AxException
	{
	public:
		AxInstanceException();
		AxInstanceException(String^ message);
	};

	public ref class AxVariableException : public AxInstanceException
	{
	public:
		AxVariableException();
		AxVariableException(String^ message);
	};

	public ref class AxVariableReadOnlyException : public AxVariableException
	{
	public:
		AxVariableReadOnlyException();
		AxVariableReadOnlyException(String^ message);
	};

	public ref class AxVariableTypeException : public AxVariableException
	{
	public:
		AxVariableTypeException();
		AxVariableTypeException(String^ message);
	};

	public ref class AxArrayIndexOutOfRangeException : public AxVariableException
	{
	public:
		AxArrayIndexOutOfRangeException();
		AxArrayIndexOutOfRangeException(String^ message);
	};
}