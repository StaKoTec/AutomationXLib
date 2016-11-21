#pragma once

using namespace System;

namespace AutomationX
{
	public enum class AxVariableType
	{
		axUndefined = 0,
		axBool = AX_BT_BOOL,
		axByte = AX_BT_BYTE,
		axShortInteger = AX_BT_SINT,
		axInteger = AX_BT_INT,
		axLongInteger = AX_BT_DINT,
		axUnsignedShortInteger = AX_BT_USINT,
		axUnsignedInteger = AX_BT_UINT,
		axUnsignedLongInteger = AX_BT_UDINT,
		axReal = AX_BT_REAL,
		axLongReal = AX_BT_LREAL,
		axString = AX_BT_STRING,
		axAlarm = AX_BT_ALARM
	};

	public ref class AxVariableValue
	{
	public:
		AxVariableType Type;
		bool BoolValue = false;
		char ByteValue = 0;
		Byte UnsignedShortIntegerValue = 0;
		char ShortIntegerValue = 0;
		Int16 IntegerValue = 0;
		Int32 LongIntegerValue = 0;
		UInt16 UnsignedIntegerValue = 0;
		UInt32 UnsignedLongIntegerValue = 0;
		Single RealValue = 0;
		Double LongRealValue = 0;
		String^ StringValue = "";
	};
}