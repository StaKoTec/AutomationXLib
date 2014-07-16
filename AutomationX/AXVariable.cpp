#include "stdafx.h"
#include "AXVariable.h"
#include "AXInstance.h"

namespace AutomationX
{
	bool AXVariable::Retentive::get()
	{
		_ax->SpsIdChanged();
		static AX_EXEC_DATA execData;
		int result = AxQueryVariable(_cName, &execData);
		if (!result) throw gcnew AXVariableException("Variable or object was not found.");
		result = AxGetRetentiveFlag(&execData);
		if (result == -1) throw gcnew AXVariableException("The variable data handle is invalid.");
		if (result == 0) return false;
		return true;
	}

	bool AXVariable::Constant::get()
	{
		_ax->SpsIdChanged();
		static AX_EXEC_DATA execData;
		int result = AxQueryVariable(_cName, &execData);
		if (!result) throw gcnew AXVariableException("Variable or object was not found.");
		result = AxGetConstantFlag(&execData);
		if (result == -1) throw gcnew AXVariableException("The variable data handle is invalid.");
		if (result == 0) return false;
		return true;
	}

	bool AXVariable::Private::get()
	{
		_ax->SpsIdChanged();
		static AX_EXEC_DATA execData;
		int result = AxQueryVariable(_cName, &execData);
		if (!result) throw gcnew AXVariableException("Variable or object was not found.");
		result = AxGetPrivateFlag(&execData);
		if (result == -1) throw gcnew AXVariableException("The variable data handle is invalid.");
		if (result == 0) return false;
		return true;
	}

	bool AXVariable::Local::get()
	{
		_ax->SpsIdChanged();
		static AX_EXEC_DATA execData;
		int result = AxQueryVariable(_cName, &execData);
		if (!result) throw gcnew AXVariableException("Variable or object was not found.");
		result = AxGetLocalFlag(&execData);
		if (result == -1) throw gcnew AXVariableException("The variable data handle is invalid.");
		if (result == 0) return false;
		return true;
	}

	bool AXVariable::ConfigurationValue::get()
	{
		_ax->SpsIdChanged();
		static AX_EXEC_DATA execData;
		int result = AxQueryVariable(_cName, &execData);
		if (!result) throw gcnew AXVariableException("Variable or object was not found.");
		result = AxGetConfValueFlag(&execData);
		if (result == -1) throw gcnew AXVariableException("The variable data handle is invalid.");
		if (result == 0) return false;
		return true;
	}

	bool AXVariable::Parameter::get()
	{
		_ax->SpsIdChanged();
		static AX_EXEC_DATA execData;
		int result = AxQueryVariable(_cName, &execData);
		if (!result) throw gcnew AXVariableException("Variable or object was not found.");
		result = AxGetParameterFlag(&execData);
		if (result == -1) throw gcnew AXVariableException("The variable data handle is invalid.");
		if (result == 0) return false;
		return true;
	}

	bool AXVariable::Remote::get()
	{
		_ax->SpsIdChanged();
		static AX_EXEC_DATA execData;
		int result = AxQueryVariable(_cName, &execData);
		if (!result) throw gcnew AXVariableException("Variable or object was not found.");
		result = AxGetRemoteFlag(&execData);
		if (result == -1) throw gcnew AXVariableException("The variable data handle is invalid.");
		if (result == 0) return false;
		return true;
	}

	bool AXVariable::NotConnected::get()
	{
		_ax->SpsIdChanged();
		static AX_EXEC_DATA execData;
		int result = AxQueryVariable(_cName, &execData);
		if (!result) throw gcnew AXVariableException("Variable or object was not found.");
		result = AxGetNcFlag(&execData);
		if (result == -1) throw gcnew AXVariableException("The variable data handle is invalid.");
		if (result == 0) return false;
		return true;
	}

	String^ AXVariable::ReferenceName::get()
	{
		_ax->SpsIdChanged();
		static AX_EXEC_DATA execData;
		int result = AxQueryVariable(_cName, &execData);
		if (!result) throw gcnew AXVariableException("Variable or object was not found.");
		const char* reference = AxGetVarReference(&execData);
		if (!reference) throw gcnew AXVariableException("The data handle is invalid, the variable is not a reference type variable or the variable is not connected.");
		return gcnew String(reference);
	}

	String^ AXVariable::Remark::get()
	{
		_ax->SpsIdChanged();
		void* handle = AxQueryExecDataEx(_cName);
		if (!handle) throw gcnew AXVariableException("Could not get variable data handle.");
		String^ value = gcnew String(AxGetRemark(handle));
		AxFreeExecData(handle);
		return value;
	}

	UInt16 AXVariable::Length::get()
	{
		_ax->SpsIdChanged();
		void* handle = AxQueryExecDataEx(_cName);
		if (!handle) throw gcnew AXVariableException("Could not get data handle.");
		UInt16 arrayLength = AxGetArrayCnt(handle);
		if (arrayLength == 0) throw gcnew AXVariableException("The variable data handle is invalid.");
		AxFreeExecData(handle);
		return arrayLength;
	}

	AXVariable::AXVariable(AXInstance^ instance, String^ name)
	{
		_instance = instance;
		_name = name;
		_cName = _converter.GetCString(_instance->Name + "." + _name);
		_ax = instance->AutomationX;
		Refresh();
		_ax->OnSpsIdChanged += gcnew AX::SpsIdChangedEventHandler(this, &AXVariable::OnSpsIdChanged);
	}

	AXVariable::~AXVariable()
	{
		if(_cName) Marshal::FreeHGlobal(IntPtr((void*)_cName)); //Always free memory!
	}

	int AXVariable::GetRawType()
	{
		_ax->SpsIdChanged();
		static AX_EXEC_DATA execData;
		int result = AxQueryVariable(_cName, &execData);
		if (!result) throw gcnew AXVariableException("Variable or object was not found.");
		return AxGetType(&execData);
	}

	void AXVariable::Clear()
	{
		int type = 0;
		try
		{
			type = GetRawType();
		}
		catch (const AXVariableException^)
		{
			throw gcnew AXVariableTypeException("Could not determinde type of variable " + _name + " and instance " + _instance->Name + ".");
		}
		if (type == AX_BT_BOOL || type == AX_BT_ALARM)
		{
			_boolValues = gcnew List<bool>(_length);
			for (int i = 0; i < _length; i++) _boolValues->Add(false);
		}
		else if (type == AX_BT_BYTE || type == AX_BT_SINT || type == AX_BT_INT || type == AX_BT_DINT || type == AX_BT_USINT || type == AX_BT_UINT || type == AX_BT_UDINT)
		{
			_integerValues = gcnew List<Int64>(_length);
			for (int i = 0; i < _length; i++) _integerValues->Add(0);
		}
		else if (type == AX_BT_REAL || type == AX_BT_LREAL)
		{
			_realValues = gcnew List<Double>(_length);
			for (int i = 0; i < _length; i++) _realValues->Add(0);
		}
		else if (type == AX_BT_STRING)
		{
			_stringValues = gcnew List<String^>(_length);
			for (int i = 0; i < _length; i++) _stringValues->Add("");
		}
		else throw gcnew AXVariableTypeException("Variable " + _name + " of instance " + _instance->Name + " has unknown type.");
	}

	void AXVariable::Refresh()
	{
		Refresh(false);
	}

	void AXVariable::Refresh(bool raiseEvents)
	{
		if (!raiseEvents)
		{
			try
			{
				_length = Length;
			}
			catch (const AXVariableException^) {}
			if (_length == 0) _length = 1;
			_isArray = _length > 1;
			Clear();
			GetAttributes();
		}
		for (UInt16 i = 0; i < _length; i++)
		{
			Refresh(i, raiseEvents);
		}
	}

	void AXVariable::Refresh(UInt16 index)
	{
		Refresh(index, false);
	}

	void AXVariable::Refresh(UInt16 index, bool raiseEvents)
	{
		_ax->SpsIdChanged();
		if (index >= _length) throw gcnew AXArrayIndexOutOfRangeException("The index exceeds the array boundaries.");
		void* handle = AxQueryExecDataEx(_cName);
		if (!handle) throw gcnew AXVariableException("Could not get variable data handle.");
		struct tagAxVariant data;
		int result = _isArray ? AxGetArray(handle, &data, index) : AxGet(handle, &data);
		if (!result)
		{
			AxFreeExecData(handle);
			throw gcnew AXVariableException("The data handle is invalid or does not represent a variable type.");
		}
		bool valueChanged = false;
		if (data.ucVarType == AX_BT_BOOL || data.ucVarType == AX_BT_ALARM)
		{
			_type = (AXVariableType)data.ucVarType;
#pragma warning (disable: 4800)
			bool newValue = data.AXVAL.btBOOL;
#pragma warning (default: 4800)
			if (_boolValues[index] != newValue)
			{
				_boolValues[index] = newValue;
				valueChanged = true;
			}
		}
		else if (data.ucVarType == AX_BT_BYTE || data.ucVarType == AX_BT_USINT)
		{
			_type = (AXVariableType)data.ucVarType;
			if (_integerValues[index] != data.AXVAL.btBYTE)
			{
				_integerValues[index] = data.AXVAL.btBYTE;
				valueChanged = true;
			}
		}
		else if (data.ucVarType == AX_BT_SINT)
		{
			_type = (AXVariableType)data.ucVarType;
			if (_integerValues[index] != data.AXVAL.btSINT)
			{
				_integerValues[index] = data.AXVAL.btSINT;
				valueChanged = true;
			}
		}
		else if (data.ucVarType == AX_BT_INT)
		{
			_type = (AXVariableType)data.ucVarType;
			if (_integerValues[index] != data.AXVAL.btINT)
			{
				_integerValues[index] = data.AXVAL.btINT;
				valueChanged = true;
			}
		}
		else if (data.ucVarType == AX_BT_DINT)
		{
			_type = (AXVariableType)data.ucVarType;
			if (_integerValues[index] != data.AXVAL.btDINT)
			{
				_integerValues[index] = data.AXVAL.btDINT;
				valueChanged = true;
			}
		}
		else if (data.ucVarType == AX_BT_UINT)
		{
			_type = (AXVariableType)data.ucVarType;
			if (_integerValues[index] != data.AXVAL.btUINT)
			{
				_integerValues[index] = data.AXVAL.btUINT;
				valueChanged = true;
			}
		}
		else if (data.ucVarType == AX_BT_UDINT)
		{
			_type = (AXVariableType)data.ucVarType;
			if (_integerValues[index] != data.AXVAL.btUDINT)
			{
				_integerValues[index] = data.AXVAL.btUDINT;
				valueChanged = true;
			}
		}
		else if (data.ucVarType == AX_BT_REAL)
		{
			_type = (AXVariableType)data.ucVarType;
			if (_realValues[index] != data.AXVAL.btREAL)
			{
				_realValues[index] = data.AXVAL.btREAL;
				valueChanged = true;
			}
		}
		else if (data.ucVarType == AX_BT_LREAL)
		{
			_type = (AXVariableType)data.ucVarType;
			if (_realValues[index] != data.AXVAL.btLREAL)
			{
				_realValues[index] = data.AXVAL.btLREAL;
				valueChanged = true;
			}
		}
		else if (data.ucVarType == AX_BT_STRING)
		{
			_type = (AXVariableType)data.ucVarType;
			String^ newValue = gcnew String(data.AXVAL.btSTRING);
			if (_stringValues[index] != newValue)
			{
				_stringValues[index] = newValue;
				valueChanged = true;
			}
		}
		else
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXVariableTypeException("The type of the variable is unknown."));
		}
		AxFreeExecData(handle);
		if (raiseEvents && valueChanged)
		{
			if (_isArray) OnArrayValueChanged(this, index); else OnValueChanged(this);
		}
	}

	void AXVariable::Set(tagAxVariant& data, UInt16 index)
	{
		_ax->SpsIdChanged();
		void* handle = AxQueryExecDataEx(_cName);
		if (!handle) throw (AXException^)(gcnew AXVariableException("Could not get variable data handle."));
		int result = _isArray ? AxSetArray(handle, &data, index) : AxSet(handle, &data);
		if (!result)
		{
			AxFreeExecData(handle);
			throw (AXException^)(gcnew AXVariableException("The data handle is invalid or does not represent a variable type."));
		}
		AxFreeExecData(handle);
	}

	bool AXVariable::GetBool()
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axBool && _type != AXVariableType::axAlarm) throw gcnew AXVariableTypeException("Variable is not of type BOOL.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		Refresh((UInt16)0);
		return _boolValues[0];
	}

	void AXVariable::Set(bool value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axBool && _type != AXVariableType::axAlarm) throw gcnew AXVariableTypeException("Variable is not of type BOOL.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btBOOL = value;
		_boolValues[0] = value;
		Set(data, 0);
	}

	bool AXVariable::GetBool(UInt16 index)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axBool && _type != AXVariableType::axAlarm) throw gcnew AXVariableTypeException("Variable is not of type BOOL.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		Refresh((UInt16)index);
		return _boolValues[index];
	}

	void AXVariable::Set(UInt16 index, bool value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axBool && _type != AXVariableType::axAlarm) throw gcnew AXVariableTypeException("Variable is not of type BOOL.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btBOOL = value;
		_boolValues[index] = value;
		Set(data, index);
	}

	Byte AXVariable::GetByte()
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axByte && _type != AXVariableType::axUnsignedShortInteger) throw gcnew AXVariableTypeException("Variable is not of type BYTE.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		Refresh((UInt16)0);
		return (Byte)_integerValues[0];
	}

	void AXVariable::Set(Byte value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axByte && _type != AXVariableType::axUnsignedShortInteger) throw gcnew AXVariableTypeException("Variable is not of type BYTE.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btBYTE = value;
		_integerValues[0] = value;
		Set(data, 0);
	}

	Byte AXVariable::GetByte(UInt16 index)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axByte && _type != AXVariableType::axUnsignedShortInteger) throw gcnew AXVariableTypeException("Variable is not of type BYTE.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		Refresh((UInt16)index);
		return (Byte)_integerValues[index];
	}

	void AXVariable::Set(UInt16 index, Byte value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axByte && _type != AXVariableType::axUnsignedShortInteger) throw gcnew AXVariableTypeException("Variable is not of type BYTE.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btBYTE = value;
		_integerValues[index] = value;
		Set(data, index);
	}

	char AXVariable::GetShortInteger()
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axShortInteger) throw gcnew AXVariableTypeException("Variable is not of type INT.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		Refresh((UInt16)0);
		return (char)_integerValues[0];
	}

	void AXVariable::Set(char value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axShortInteger) throw gcnew AXVariableTypeException("Variable is not of type SINT.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btSINT = value;
		_integerValues[0] = value;
		Set(data, 0);
	}

	char AXVariable::GetShortInteger(UInt16 index)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axShortInteger) throw gcnew AXVariableTypeException("Variable is not of type SINT.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		Refresh((UInt16)index);
		return (char)_integerValues[index];
	}

	void AXVariable::Set(UInt16 index, char value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axShortInteger) throw gcnew AXVariableTypeException("Variable is not of type SINT.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btSINT = value;
		_integerValues[index] = value;
		Set(data, index);
	}

	Int16 AXVariable::GetInteger()
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axInteger) throw gcnew AXVariableTypeException("Variable is not of type SINT.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		Refresh((UInt16)0);
		return (Int16)_integerValues[0];
	}

	void AXVariable::Set(Int16 value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axInteger) throw gcnew AXVariableTypeException("Variable is not of type INT.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btINT = value;
		_integerValues[0] = value;
		Set(data, 0);
	}

	Int16 AXVariable::GetInteger(UInt16 index)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axInteger) throw gcnew AXVariableTypeException("Variable is not of type INT.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		Refresh((UInt16)index);
		return (Int16)_integerValues[index];
	}

	void AXVariable::Set(UInt16 index, Int16 value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axInteger) throw gcnew AXVariableTypeException("Variable is not of type INT.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btINT = value;
		_integerValues[index] = value;
		Set(data, index);
	}

	Int32 AXVariable::GetLongInteger()
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axLongInteger) throw gcnew AXVariableTypeException("Variable is not of type DINT.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		Refresh((UInt16)0);
		return (Int32)_integerValues[0];
	}

	void AXVariable::Set(Int32 value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axLongInteger) throw gcnew AXVariableTypeException("Variable is not of type DINT.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btDINT = value;
		_integerValues[0] = value;
		Set(data, 0);
	}

	Int32 AXVariable::GetLongInteger(UInt16 index)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axLongInteger) throw gcnew AXVariableTypeException("Variable is not of type DINT.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		Refresh((UInt16)index);
		return (Int32)_integerValues[index];
	}

	void AXVariable::Set(UInt16 index, Int32 value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axLongInteger) throw gcnew AXVariableTypeException("Variable is not of type DINT.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btDINT = value;
		_integerValues[index] = value;
		Set(data, index);
	}

	UInt16 AXVariable::GetUnsignedInteger()
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axUnsignedInteger) throw gcnew AXVariableTypeException("Variable is not of type UINT.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		Refresh((UInt16)0);
		return (UInt16)_integerValues[0];
	}

	void AXVariable::Set(UInt16 value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axUnsignedInteger) throw gcnew AXVariableTypeException("Variable is not of type UINT.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btUINT = value;
		_integerValues[0] = value;
		Set(data, 0);
	}

	UInt16 AXVariable::GetUnsignedInteger(UInt16 index)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axUnsignedInteger) throw gcnew AXVariableTypeException("Variable is not of type UINT.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		Refresh((UInt16)index);
		return (UInt16)_integerValues[index];
	}

	void AXVariable::Set(UInt16 index, UInt16 value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axUnsignedInteger) throw gcnew AXVariableTypeException("Variable is not of type UINT.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btUINT = value;
		_integerValues[index] = value;
		Set(data, index);
	}

	UInt32 AXVariable::GetUnsignedLongInteger()
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axUnsignedLongInteger) throw gcnew AXVariableTypeException("Variable is not of type UDINT.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		Refresh((UInt16)0);
		return (UInt32)_integerValues[0];
	}

	void AXVariable::Set(UInt32 value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axUnsignedLongInteger) throw gcnew AXVariableTypeException("Variable is not of type UDINT.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btUDINT = value;
		_integerValues[0] = value;
		Set(data, 0);
	}

	UInt32 AXVariable::GetUnsignedLongInteger(UInt16 index)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axUnsignedLongInteger) throw gcnew AXVariableTypeException("Variable is not of type UDINT.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		Refresh((UInt16)index);
		return (UInt32)_integerValues[index];
	}

	void AXVariable::Set(UInt16 index, UInt32 value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axUnsignedLongInteger) throw gcnew AXVariableTypeException("Variable is not of type UDINT.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btUDINT = value;
		_integerValues[index] = value;
		Set(data, index);
	}

	Single AXVariable::GetReal()
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axReal) throw gcnew AXVariableTypeException("Variable is not of type REAL.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		Refresh((UInt16)0);
		return (Single)_realValues[0];
	}

	void AXVariable::Set(Single value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axReal) throw gcnew AXVariableTypeException("Variable is not of type REAL.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btREAL = value;
		_realValues[0] = value;
		Set(data, 0);
	}

	Single AXVariable::GetReal(UInt16 index)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axReal) throw gcnew AXVariableTypeException("Variable is not of type REAL.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		Refresh((UInt16)index);
		return (Single)_realValues[index];
	}

	void AXVariable::Set(UInt16 index, Single value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axReal) throw gcnew AXVariableTypeException("Variable is not of type REAL.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btREAL = value;
		_realValues[index] = value;
		Set(data, index);
	}

	Double AXVariable::GetLongReal()
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axLongReal) throw gcnew AXVariableTypeException("Variable is not of type REAL.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		Refresh((UInt16)0);
		return _realValues[0];
	}

	void AXVariable::Set(Double value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axLongReal) throw gcnew AXVariableTypeException("Variable is not of type REAL.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btLREAL = value;
		_realValues[0] = value;
		Set(data, 0);
	}

	Double AXVariable::GetLongReal(UInt16 index)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axLongReal) throw gcnew AXVariableTypeException("Variable is not of type REAL.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		Refresh((UInt16)index);
		return _realValues[index];
	}

	void AXVariable::Set(UInt16 index, Double value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axLongReal) throw gcnew AXVariableTypeException("Variable is not of type REAL.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		data.AXVAL.btLREAL = value;
		_realValues[index] = value;
		Set(data, index);
	}

	String^ AXVariable::GetString()
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axString) throw gcnew AXVariableTypeException("Variable is not of type STRING.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		Refresh((UInt16)0);
		return _stringValues[0];
	}

	void AXVariable::Set(String^ value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axString) throw gcnew AXVariableTypeException("Variable is not of type STRING.");
		if (_isArray) throw gcnew AXVariableTypeException("Variable is an array. Please specify the element index.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		strcpy_s(data.AXVAL.btSTRING, _converter.GetString(value).c_str());
		_stringValues[0] = value;
		Set(data, 0);
	}

	String^ AXVariable::GetString(UInt16 index)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axString) throw gcnew AXVariableTypeException("Variable is not of type STRING.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		Refresh((UInt16)index);
		return _stringValues[index];
	}

	void AXVariable::Set(UInt16 index, String^ value)
	{
		_ax->SpsIdChanged();
		if (_type != AXVariableType::axString) throw gcnew AXVariableTypeException("Variable is not of type STRING.");
		if (!_isArray) throw gcnew AXVariableTypeException("Variable is no array.");
		struct tagAxVariant data;
		data.ucVarType = (unsigned char)_type;
		strcpy_s(data.AXVAL.btSTRING, _converter.GetString(value).c_str());
		_stringValues[index] = value;
		Set(data, index);
	}

	void AXVariable::OnSpsIdChanged(AX^ sender)
	{
		Refresh();
	}

	void AXVariable::GetAttributes()
	{
		_ax->SpsIdChanged();
		static AX_EXEC_DATA execData;
		int result = AxQueryVariable(_cName, &execData);
		if (!result) throw gcnew AXVariableException("Variable or object was not found.");
		AX_ATTR attrs;
		if (AxGetAttributes(&execData, &attrs) == -1) throw gcnew AXVariableException("The variable data handle is invalid.");
		_decimalPoints = attrs.dec_point;
		if (attrs.dim) _dimension = gcnew String(attrs.dim);
		if (attrs.rem == 0) _global = false; else _global = true;
		if (attrs.trend == 0) _trending = false; else _trending = true;
	}
}
