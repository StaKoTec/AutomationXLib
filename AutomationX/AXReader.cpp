#include "stdafx.h"
#include "AXReader.h"

namespace AutomationX
{
	AXReader::AXReader(AX^ ax)
	{
		_ax = ax;
	}

	bool AXReader::ReadBool(String^ variableName)
	{
		return ReadBool(_ax->GetInstanceName(), variableName);
	}

	bool AXReader::ReadBool(String^ instanceName, String^ variableName)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_BOOL;
		if (!AxGet(handle, &data))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid or does not represent a variable type."));
		}
		bool value = (bool)data.AXVAL.btBOOL;
		AxFreeExecData(handle);
		return value;
	}

	bool AXReader::ReadBoolArray(String^ variableName, UInt16 index)
	{
		return ReadBoolArray(_ax->GetInstanceName(), variableName, index);
	}

	bool AXReader::ReadBoolArray(String^ instanceName, String^ variableName, UInt16 index)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_BOOL;
		if (!AxGetArray(handle, &data, index))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid, does not represent a variable type or the index was out of range."));
		}
		bool value = (bool)data.AXVAL.btBOOL;
		AxFreeExecData(handle);
		return value;
	}

	Byte AXReader::ReadByte(String^ variableName)
	{
		return ReadByte(_ax->GetInstanceName(), variableName);
	}

	Byte AXReader::ReadByte(String^ instanceName, String^ variableName)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_BYTE;
		if (!AxGet(handle, &data))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid or does not represent a variable type."));
		}
		Byte value = data.AXVAL.btBYTE;
		AxFreeExecData(handle);
		return value;
	}

	Byte AXReader::ReadByteArray(String^ variableName, UInt16 index)
	{
		return ReadByteArray(_ax->GetInstanceName(), variableName, index);
	}

	Byte AXReader::ReadByteArray(String^ instanceName, String^ variableName, UInt16 index)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_BYTE;
		if (!AxGetArray(handle, &data, index))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid, does not represent a variable type or the index was out of range."));
		}
		Byte value = data.AXVAL.btBYTE;
		AxFreeExecData(handle);
		return value;
	}

	Int16 AXReader::ReadInteger(String^ variableName)
	{
		return ReadInteger(_ax->GetInstanceName(), variableName);
	}

	Int16 AXReader::ReadInteger(String^ instanceName, String^ variableName)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_INT;
		if (!AxGet(handle, &data))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid or does not represent a variable type."));
		}
		Int16 value = data.AXVAL.btINT;
		AxFreeExecData(handle);
		return value;
	}

	Int16 AXReader::ReadIntegerArray(String^ variableName, UInt16 index)
	{
		return ReadIntegerArray(_ax->GetInstanceName(), variableName, index);
	}

	Int16 AXReader::ReadIntegerArray(String^ instanceName, String^ variableName, UInt16 index)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_INT;
		if (!AxGetArray(handle, &data, index))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid, does not represent a variable type or the index was out of range."));
		}
		Int16 value = data.AXVAL.btINT;
		AxFreeExecData(handle);
		return value;
	}

	Int32 AXReader::ReadLongInteger(String^ variableName)
	{
		return ReadLongInteger(_ax->GetInstanceName(), variableName);
	}

	Int32 AXReader::ReadLongInteger(String^ instanceName, String^ variableName)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_DINT;
		if (!AxGet(handle, &data))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid or does not represent a variable type."));
		}
		Int32 value = data.AXVAL.btDINT;
		AxFreeExecData(handle);
		return value;
	}

	Int32 AXReader::ReadLongIntegerArray(String^ variableName, UInt16 index)
	{
		return ReadLongIntegerArray(_ax->GetInstanceName(), variableName, index);
	}

	Int32 AXReader::ReadLongIntegerArray(String^ instanceName, String^ variableName, UInt16 index)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_DINT;
		if (!AxGetArray(handle, &data, index))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid, does not represent a variable type or the index was out of range."));
		}
		Int32 value = data.AXVAL.btDINT;
		AxFreeExecData(handle);
		return value;
	}

	UInt16 AXReader::ReadUnsignedInteger(String^ variableName)
	{
		return ReadUnsignedInteger(_ax->GetInstanceName(), variableName);
	}

	UInt16 AXReader::ReadUnsignedInteger(String^ instanceName, String^ variableName)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_UINT;
		if (!AxGet(handle, &data))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid or does not represent a variable type."));
		}
		UInt16 value = data.AXVAL.btUINT;
		AxFreeExecData(handle);
		return value;
	}

	UInt16 AXReader::ReadUnsignedIntegerArray(String^ variableName, UInt16 index)
	{
		return ReadUnsignedIntegerArray(_ax->GetInstanceName(), variableName, index);
	}

	UInt16 AXReader::ReadUnsignedIntegerArray(String^ instanceName, String^ variableName, UInt16 index)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_UINT;
		if (!AxGetArray(handle, &data, index))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid, does not represent a variable type or the index was out of range."));
		}
		UInt16 value = data.AXVAL.btUINT;
		AxFreeExecData(handle);
		return value;
	}

	UInt32 AXReader::ReadUnsignedLongInteger(String^ variableName)
	{
		return ReadUnsignedLongInteger(_ax->GetInstanceName(), variableName);
	}

	UInt32 AXReader::ReadUnsignedLongInteger(String^ instanceName, String^ variableName)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_UDINT;
		if (!AxGet(handle, &data))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid or does not represent a variable type."));
		}
		UInt32 value = data.AXVAL.btUDINT;
		AxFreeExecData(handle);
		return value;
	}

	UInt32 AXReader::ReadUnsignedLongIntegerArray(String^ variableName, UInt16 index)
	{
		return ReadUnsignedLongIntegerArray(_ax->GetInstanceName(), variableName, index);
	}

	UInt32 AXReader::ReadUnsignedLongIntegerArray(String^ instanceName, String^ variableName, UInt16 index)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_UDINT;
		if (!AxGetArray(handle, &data, index))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid, does not represent a variable type or the index was out of range."));
		}
		UInt32 value = data.AXVAL.btUDINT;
		AxFreeExecData(handle);
		return value;
	}

	Double AXReader::ReadReal(String^ variableName)
	{
		return ReadReal(_ax->GetInstanceName(), variableName);
	}

	Double AXReader::ReadReal(String^ instanceName, String^ variableName)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_REAL;
		if (!AxGet(handle, &data))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid or does not represent a variable type."));
		}
		Double value = data.AXVAL.btREAL;
		AxFreeExecData(handle);
		return value;
	}

	Double AXReader::ReadRealArray(String^ variableName, UInt16 index)
	{
		return ReadRealArray(_ax->GetInstanceName(), variableName, index);
	}

	Double AXReader::ReadRealArray(String^ instanceName, String^ variableName, UInt16 index)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_REAL;
		if (!AxGetArray(handle, &data, index))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid, does not represent a variable type or the index was out of range."));
		}
		Double value = data.AXVAL.btREAL;
		AxFreeExecData(handle);
		return value;
	}

	String^ AXReader::ReadString(String^ variableName)
	{
		return ReadString(_ax->GetInstanceName(), variableName);
	}

	String^ AXReader::ReadString(String^ instanceName, String^ variableName)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_STRING;
		if (!AxGet(handle, &data))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid or does not represent a variable type."));
		}
		String^ value = gcnew String(data.AXVAL.btSTRING);
		AxFreeExecData(handle);
		return value;
	}

	String^ AXReader::ReadStringArray(String^ variableName, UInt16 index)
	{
		return ReadStringArray(_ax->GetInstanceName(), variableName, index);
	}

	String^ AXReader::ReadStringArray(String^ instanceName, String^ variableName, UInt16 index)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_STRING;
		if (!AxGetArray(handle, &data, index))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid, does not represent a variable type or the index was out of range."));
		}
		String^ value = gcnew String(data.AXVAL.btSTRING);
		AxFreeExecData(handle);
		return value;
	}

	UInt16 AXReader::GetDecimalPoints(String^ variableName)
	{
		return GetDecimalPoints(_ax->GetInstanceName(), variableName);
	}

	UInt16 AXReader::GetDecimalPoints(String^ instanceName, String^ variableName)
	{
		_ax->CheckRunning();
		static AX_EXEC_DATA execData;
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		int result = AxQueryVariable(cName, &execData);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!result) throw (AXException^)(gcnew AXException("Variable or object was not found."));
		UInt16 value = AxGetDecPoint(&execData);
		return value;
	}

	System::Collections::Generic::List<String^>^ AXReader::GetInstanceNames(String^ className)
	{
		_ax->CheckRunning();
		System::Collections::Generic::List<String^>^ instanceNames = gcnew System::Collections::Generic::List<String^>();
		char* cName = _converter.GetCString(className);
		AX_INSTANCE data = nullptr;
		while (data = AxGetInstance(data, cName))
		{
			if (!data) break;
			String^ instanceName = gcnew String(AxGetInstanceName(data));
			if (instanceName->Length == 0) continue;
			instanceNames->Add(instanceName);
		}
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		return instanceNames;
	}

	UInt16 AXReader::GetArrayLength(String^ variableName)
	{
		return GetArrayLength(_ax->GetInstanceName(), variableName);
	}

	UInt16 AXReader::GetArrayLength(String^ instanceName, String^ variableName)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		UInt16 arrayLength = AxGetArrayCnt(handle);
		if (arrayLength == 0) throw (AXException^)(gcnew AXException("The data handle is invalid."));
		AxFreeExecData(handle);
		return arrayLength;
	}

	bool AXReader::VariableExists(String^ variableName)
	{
		return VariableExists(_ax->GetInstanceName(), variableName);
	}

	bool AXReader::VariableExists(String^ instanceName, String^ variableName)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) return false;
		AxFreeExecData(handle);
		return true;
	}

	String^ AXReader::GetReferenceName(String^ variableName)
	{
		return GetReferenceName(_ax->GetInstanceName(), variableName);
	}

	String^ AXReader::GetReferenceName(String^ instanceName, String^ variableName)
	{
		_ax->CheckRunning();
		static AX_EXEC_DATA execData;
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		int result = AxQueryVariable(cName, &execData);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!result) throw (AXException^)(gcnew AXException("Variable or object was not found."));
		const char* reference = AxGetVarReference(&execData);
		if (!reference) throw (AXException^)(gcnew AXException("The data handle is invalid, the variable is not a reference type variable or the variable is not connected."));
		return gcnew String(reference);
	}

	String^ AXReader::GetVariableRemark(String^ variableName)
	{
		return GetVariableRemark(_ax->GetInstanceName(), variableName);
	}

	String^ AXReader::GetVariableRemark(String^ instanceName, String^ variableName)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		String^ value = gcnew String(AxGetRemark(handle));
		AxFreeExecData(handle);
		return value;
	}

	String^ AXReader::GetInstanceRemark()
	{
		return GetInstanceRemark(_ax->GetInstanceName());
	}

	String^ AXReader::GetInstanceRemark(String^ instanceName)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName);
		void* handle = AxQueryInstance(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get instance handle."));
		String^ value = gcnew String(AxGetInstanceRemark(handle));
		return value;
	}
}