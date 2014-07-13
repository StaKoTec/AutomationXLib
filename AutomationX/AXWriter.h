#pragma once

using namespace System;

#include "ManagedTypeConverter.h"

namespace AutomationX
{
	ref class AX;

	public ref class AXWriter
	{
	private:
		AX^ _ax;
		ManagedTypeConverter _converter;
	public:
		AXWriter(AX^ ax);

		void WriteBool(String^ variableName, bool value);
		void WriteBool(String^ instanceName, String^ variableName, bool value);
		void WriteBoolArray(String^ variableName, UInt16 index, bool value);
		void WriteBoolArray(String^ instanceName, String^ variableName, UInt16 index, bool value);
		void WriteByte(String^ variableName, Byte value);
		void WriteByte(String^ instanceName, String^ variableName, Byte value);
		void WriteByteArray(String^ variableName, UInt16 index, Byte value);
		void WriteByteArray(String^ instanceName, String^ variableName, UInt16 index, Byte value);
		void WriteInteger(String^ variableName, Int16 value);
		void WriteInteger(String^ instanceName, String^ variableName, Int16 value);
		void WriteIntegerArray(String^ variableName, UInt16 index, Int16 value);
		void WriteIntegerArray(String^ instanceName, String^ variableName, UInt16 index, Int16 value);
		void WriteLongInteger(String^ variableName, Int32 value);
		void WriteLongInteger(String^ instanceName, String^ variableName, Int32 value);
		void WriteLongIntegerArray(String^ variableName, UInt16 index, Int32 value);
		void WriteLongIntegerArray(String^ instanceName, String^ variableName, UInt16 index, Int32 value);
		void WriteUnsignedInteger(String^ variableName, UInt16 value);
		void WriteUnsignedInteger(String^ instanceName, String^ variableName, UInt16 value);
		void WriteUnsignedIntegerArray(String^ variableName, UInt16 index, UInt16 value);
		void WriteUnsignedIntegerArray(String^ instanceName, String^ variableName, UInt16 index, UInt16 value);
		void WriteUnsignedLongInteger(String^ variableName, UInt32 value);
		void WriteUnsignedLongInteger(String^ instanceName, String^ variableName, UInt32 value);
		void WriteUnsignedLongIntegerArray(String^ variableName, UInt16 index, UInt32 value);
		void WriteUnsignedLongIntegerArray(String^ instanceName, String^ variableName, UInt16 index, UInt32 value);
		void WriteReal(String^ variableName, Single value);
		void WriteReal(String^ instanceName, String^ variableName, Single value);
		void WriteRealArray(String^ variableName, UInt16 index, Single value);
		void WriteRealArray(String^ instanceName, String^ variableName, UInt16 index, Single value);
		void WriteString(String^ variableName, String^ value);
		void WriteString(String^ instanceName, String^ variableName, String^ value);
		void WriteStringArray(String^ variableName, UInt16 index, String^ value);
		void WriteStringArray(String^ instanceName, String^ variableName, UInt16 index, String^ value);
	};
}