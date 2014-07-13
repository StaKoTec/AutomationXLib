#pragma once

using namespace System;

#include "ManagedTypeConverter.h"

namespace AutomationX
{
	ref class AX;

	public ref class AXReader
	{
	private:
		AX^ _ax;
		ManagedTypeConverter _converter;
	public:
		AXReader(AX^ ax);

		UInt16 GetDecimalPoints(String^ variableName);
		UInt16 GetDecimalPoints(String^ instanceName, String^ variableName);
		System::Collections::Generic::List<String^>^ GetInstanceNames(String^ className);
		UInt16 GetArrayLength(String^ variableName);
		UInt16 GetArrayLength(String^ instanceName, String^ variableName);
		bool VariableExists(String^ variableName);
		bool VariableExists(String^ instanceName, String^ variableName);
		String^ GetReferenceName(String^ variableName);
		String^ GetReferenceName(String^ instanceName, String^ variableName);
		String^ GetVariableRemark(String^ variableName);
		String^ GetVariableRemark(String^ instanceName, String^ variableName);
		String^ GetInstanceRemark();
		String^ GetInstanceRemark(String^ instanceName);

		bool ReadBool(String^ variableName);
		bool ReadBool(String^ instanceName, String^ variableName);
		bool ReadBoolArray(String^ variableName, UInt16 index);
		bool ReadBoolArray(String^ instanceName, String^ variableName, UInt16 index);
		Byte ReadByte(String^ variableName);
		Byte ReadByte(String^ instanceName, String^ variableName);
		Byte ReadByteArray(String^ variableName, UInt16 index);
		Byte ReadByteArray(String^ instanceName, String^ variableName, UInt16 index);
		Int16 ReadInteger(String^ variableName);
		Int16 ReadInteger(String^ instanceName, String^ variableName);
		Int16 ReadIntegerArray(String^ variableName, UInt16 index);
		Int16 ReadIntegerArray(String^ instanceName, String^ variableName, UInt16 index);
		Int32 ReadLongInteger(String^ variableName);
		Int32 ReadLongInteger(String^ instanceName, String^ variableName);
		Int32 ReadLongIntegerArray(String^ variableName, UInt16 index);
		Int32 ReadLongIntegerArray(String^ instanceName, String^ variableName, UInt16 index);
		UInt16 ReadUnsignedInteger(String^ variableName);
		UInt16 ReadUnsignedInteger(String^ instanceName, String^ variableName);
		UInt16 ReadUnsignedIntegerArray(String^ variableName, UInt16 index);
		UInt16 ReadUnsignedIntegerArray(String^ instanceName, String^ variableName, UInt16 index);
		UInt32 ReadUnsignedLongInteger(String^ variableName);
		UInt32 ReadUnsignedLongInteger(String^ instanceName, String^ variableName);
		UInt32 ReadUnsignedLongIntegerArray(String^ variableName, UInt16 index);
		UInt32 ReadUnsignedLongIntegerArray(String^ instanceName, String^ variableName, UInt16 index);
		Single ReadReal(String^ variableName);
		Single ReadReal(String^ instanceName, String^ variableName);
		Single ReadRealArray(String^ variableName, UInt16 index);
		Single ReadRealArray(String^ instanceName, String^ variableName, UInt16 index);
		String^ ReadString(String^ variableName);
		String^ ReadString(String^ instanceName, String^ variableName);
		String^ ReadStringArray(String^ variableName, UInt16 index);
		String^ ReadStringArray(String^ instanceName, String^ variableName, UInt16 index);
	};
}