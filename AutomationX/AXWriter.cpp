#include "stdafx.h"
#include "AXWriter.h"

namespace AutomationX
{
	AXWriter::AXWriter(AX^ ax)
	{
		_ax = ax;
	}

	void AXWriter::WriteBool(String^ variableName, bool value)
	{
		return WriteBool(_ax->GetInstanceName(), variableName, value);
	}

	void AXWriter::WriteBool(String^ instanceName, String^ variableName, bool value)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_BOOL;
		data.AXVAL.btBOOL = value;
		if (!AxSet(handle, &data))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid or does not represent a variable type."));
		}
		AxFreeExecData(handle);
	}

	void AXWriter::WriteBoolArray(String^ variableName, UInt16 index, bool value)
	{
		WriteBoolArray(_ax->GetInstanceName(), variableName, index, value);
	}

	void AXWriter::WriteBoolArray(String^ instanceName, String^ variableName, UInt16 index, bool value)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_BOOL;
		data.AXVAL.btBOOL = value;
		if (!AxSetArray(handle, &data, index))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid, does not represent a variable type or the index was out of range."));
		}
		AxFreeExecData(handle);
	}

	void AXWriter::WriteByte(String^ variableName, Byte value)
	{
		WriteByte(_ax->GetInstanceName(), variableName, value);
	}

	void AXWriter::WriteByte(String^ instanceName, String^ variableName, Byte value)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_BYTE;
		data.AXVAL.btBYTE = value;
		if (!AxSet(handle, &data))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid or does not represent a variable type."));
		}
		AxFreeExecData(handle);
	}

	void AXWriter::WriteByteArray(String^ variableName, UInt16 index, Byte value)
	{
		WriteByteArray(_ax->GetInstanceName(), variableName, index, value);
	}

	void AXWriter::WriteByteArray(String^ instanceName, String^ variableName, UInt16 index, Byte value)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_BYTE;
		data.AXVAL.btBYTE = value;
		if (!AxSetArray(handle, &data, index))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid, does not represent a variable type or the index was out of range."));
		}
		AxFreeExecData(handle);
	}

	void AXWriter::WriteInteger(String^ variableName, Int16 value)
	{
		WriteInteger(_ax->GetInstanceName(), variableName, value);
	}

	void AXWriter::WriteInteger(String^ instanceName, String^ variableName, Int16 value)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_INT;
		data.AXVAL.btINT = value;
		if (!AxSet(handle, &data))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid or does not represent a variable type."));
		}
		AxFreeExecData(handle);
	}

	void AXWriter::WriteIntegerArray(String^ variableName, UInt16 index, Int16 value)
	{
		WriteIntegerArray(_ax->GetInstanceName(), variableName, index, value);
	}

	void AXWriter::WriteIntegerArray(String^ instanceName, String^ variableName, UInt16 index, Int16 value)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_INT;
		data.AXVAL.btINT = value;
		if (!AxSetArray(handle, &data, index))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid, does not represent a variable type or the index was out of range."));
		}
		AxFreeExecData(handle);
	}

	void AXWriter::WriteLongInteger(String^ variableName, Int32 value)
	{
		WriteLongInteger(_ax->GetInstanceName(), variableName, value);
	}

	void AXWriter::WriteLongInteger(String^ instanceName, String^ variableName, Int32 value)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_DINT;
		data.AXVAL.btDINT = value;
		if (!AxSet(handle, &data))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid or does not represent a variable type."));
		}
		AxFreeExecData(handle);
	}

	void AXWriter::WriteLongIntegerArray(String^ variableName, UInt16 index, Int32 value)
	{
		WriteLongIntegerArray(_ax->GetInstanceName(), variableName, index, value);
	}

	void AXWriter::WriteLongIntegerArray(String^ instanceName, String^ variableName, UInt16 index, Int32 value)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_DINT;
		data.AXVAL.btDINT = value;
		if (!AxSetArray(handle, &data, index))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid, does not represent a variable type or the index was out of range."));
		}
		AxFreeExecData(handle);
	}

	void AXWriter::WriteUnsignedInteger(String^ variableName, UInt16 value)
	{
		WriteUnsignedInteger(_ax->GetInstanceName(), variableName, value);
	}

	void AXWriter::WriteUnsignedInteger(String^ instanceName, String^ variableName, UInt16 value)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_UINT;
		data.AXVAL.btUINT = value;
		if (!AxSet(handle, &data))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid or does not represent a variable type."));
		}
		AxFreeExecData(handle);
	}

	void AXWriter::WriteUnsignedIntegerArray(String^ variableName, UInt16 index, UInt16 value)
	{
		WriteUnsignedIntegerArray(_ax->GetInstanceName(), variableName, index, value);
	}

	void AXWriter::WriteUnsignedIntegerArray(String^ instanceName, String^ variableName, UInt16 index, UInt16 value)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_UINT;
		data.AXVAL.btUINT = value;
		if (!AxSetArray(handle, &data, index))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid, does not represent a variable type or the index was out of range."));
		}
		AxFreeExecData(handle);
	}

	void AXWriter::WriteUnsignedLongInteger(String^ variableName, UInt32 value)
	{
		WriteUnsignedLongInteger(_ax->GetInstanceName(), variableName, value);
	}

	void AXWriter::WriteUnsignedLongInteger(String^ instanceName, String^ variableName, UInt32 value)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_UDINT;
		data.AXVAL.btUDINT = value;
		if (!AxSet(handle, &data))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid or does not represent a variable type."));
		}
		AxFreeExecData(handle);
	}

	void AXWriter::WriteUnsignedLongIntegerArray(String^ variableName, UInt16 index, UInt32 value)
	{
		WriteUnsignedLongIntegerArray(_ax->GetInstanceName(), variableName, index, value);
	}

	void AXWriter::WriteUnsignedLongIntegerArray(String^ instanceName, String^ variableName, UInt16 index, UInt32 value)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_UDINT;
		data.AXVAL.btUDINT = value;
		if (!AxSetArray(handle, &data, index))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid, does not represent a variable type or the index was out of range."));
		}
		AxFreeExecData(handle);
	}

	void AXWriter::WriteReal(String^ variableName, Double value)
	{
		WriteReal(_ax->GetInstanceName(), variableName, value);
	}

	void AXWriter::WriteReal(String^ instanceName, String^ variableName, Double value)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_REAL;
		data.AXVAL.btREAL = value;
		if (!AxSet(handle, &data))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid or does not represent a variable type."));
		}
		AxFreeExecData(handle);
	}

	void AXWriter::WriteRealArray(String^ variableName, UInt16 index, Double value)
	{
		WriteRealArray(_ax->GetInstanceName(), variableName, index, value);
	}

	void AXWriter::WriteRealArray(String^ instanceName, String^ variableName, UInt16 index, Double value)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_REAL;
		data.AXVAL.btREAL = value;
		if (!AxSetArray(handle, &data, index))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid, does not represent a variable type or the index was out of range."));
		}
		AxFreeExecData(handle);
	}

	void AXWriter::WriteString(String^ variableName, String^ value)
	{
		WriteString(_ax->GetInstanceName(), variableName, value);
	}

	void AXWriter::WriteString(String^ instanceName, String^ variableName, String^ value)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_STRING;
		strcpy_s(data.AXVAL.btSTRING, _converter.GetString(value).c_str());
		if (!AxSet(handle, &data))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid or does not represent a variable type."));
		}
		AxFreeExecData(handle);
	}

	void AXWriter::WriteStringArray(String^ variableName, UInt16 index, String^ value)
	{
		WriteStringArray(_ax->GetInstanceName(), variableName, index, value);
	}

	void AXWriter::WriteStringArray(String^ instanceName, String^ variableName, UInt16 index, String^ value)
	{
		_ax->CheckRunning();
		char* cName = _converter.GetCString(instanceName + "." + variableName);
		void* handle = AxQueryExecDataEx(cName);
		Marshal::FreeHGlobal(IntPtr((void*)cName)); //Always free memory!
		if (!handle) throw (AXException^)(gcnew AXException("Could not get data handle."));
		struct tagAxVariant data;
		data.ucVarType = AX_BT_STRING;
		strcpy_s(data.AXVAL.btSTRING, _converter.GetString(value).c_str());
		if (!AxSetArray(handle, &data, index))
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXException("The data handle is invalid, does not represent a variable type or the index was out of range."));
		}
		AxFreeExecData(handle);
	}
}