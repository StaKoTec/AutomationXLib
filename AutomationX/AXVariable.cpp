#include "stdafx.h"
#include "AxVariable.h"

namespace AutomationX
{
	bool AxVariable::Events::get()
	{
		return _events;
	}

	void AxVariable::Events::set(bool value)
	{
		_events = value;
		if (_events) _pollId = _ax->AddVariableToPoll(this);
		else _ax->RemoveVariableToPoll(_pollId);
	}

	String^ AxVariable::Path::get()
	{
		return _path;
	}

	AxVariable::AxVariable(AxInstance^ instance, String^ name)
	{
		_ax = instance->AxObject;
		_instance = instance;
		_name = name;
		_path = instance->Path + "." + _name;
		_cName = _converter.GetCString(_path);
		GetExecData();
		if (!_execData) throw gcnew AxVariableException("The variable " + _path + " was not found.");
	}

	AxVariable::~AxVariable()
	{
		this->!AxVariable();
	}

	AxVariable::!AxVariable()
	{
		_ax->RemoveVariableToPoll(_pollId);
		if (_cName) Marshal::FreeHGlobal(IntPtr((void*)_cName));
		_cName = nullptr;
		_instance = nullptr;
		if (_boolValues) _boolValues->Clear();
		_boolValues = nullptr;
		if (_integerValues) _integerValues->Clear();
		_integerValues = nullptr;
		if (_stringValues) _stringValues->Clear();
		_stringValues = nullptr;
		if (_realValues) _realValues->Clear();
		_realValues = nullptr;
		if (_execData) AxFreeExecData(_execData);
		_execData = nullptr;
	}

	void AxVariable::RaiseValueChanged()
	{
		try
		{
			ValueChanged(this);
		}
		catch (Exception^ ex)
		{
			System::Diagnostics::Debug::WriteLine(ex->Message + " " + ex->StackTrace);
		}
	}

	void AxVariable::RaiseArrayValueChanged(UInt16 index)
	{
		try
		{
			ArrayValueChanged(this, index);
		}
		catch (Exception^ ex)
		{
			System::Diagnostics::Debug::WriteLine(ex->Message + " " + ex->StackTrace);
		}
	}

	void AxVariable::GetExecData()
	{
		if (_execData) AxFreeExecData(_execData);
		_execData = AxQueryExecDataEx(_cName);
	}

	void AxVariable::ReloadStaticProperties(bool wait)
	{
		_initResetEvent->Reset();
		GetLength(); // Needed by GetType()
		GetReferenceName();
		GetDeclaration();
		GetType(); // Needed by GetFlags()
		GetRemark();
		GetFlags(wait); //Waits to be finished if "wait" is true
	}

	// {{{ Queued init methods
	void AxVariable::InvokeGetReferenceName()
	{
		const char* reference = AxGetVarReference(_execData);
		if (reference) _referenceName = gcnew String(reference);
		// Todo: Wird nicht für Klassenreferenzen und Input-Referenzen zurückgegeben.
	}

	void AxVariable::GetReferenceName()
	{
		_ax->QueueInitFunction(Binder::Bind(gcnew NoParameterDelegate(this, &AxVariable::InvokeGetReferenceName)));
	}

	void AxVariable::InvokeGetDeclaration()
	{
		int declaration = AxGetVarDeclaration(_execData);
		_declaration = (AxVariableDeclaration)declaration;
	}

	void AxVariable::GetDeclaration()
	{
		_ax->QueueInitFunction(Binder::Bind(gcnew NoParameterDelegate(this, &AxVariable::InvokeGetDeclaration)));
	}

	void AxVariable::InvokeGetType()
	{
		struct tagAxVariant data;
		int result = _isArray ? AxGetArray(_execData, &data, 0) : AxGet(_execData, &data);
		if (result) _type = (AxVariableType)data.ucVarType;
		else _type = AxVariableType::axUndefined;

		if (_type == AxVariableType::axBool || _type == AxVariableType::axAlarm) _boolValues = System::Linq::Enumerable::ToList(System::Linq::Enumerable::Repeat(false, _length));
		else if (_type == AxVariableType::axByte || _type == AxVariableType::axUnsignedShortInteger || _type == AxVariableType::axShortInteger || _type == AxVariableType::axInteger || _type == AxVariableType::axLongInteger || _type == AxVariableType::axUnsignedInteger || _type == AxVariableType::axUnsignedLongInteger) _integerValues = System::Linq::Enumerable::ToList(System::Linq::Enumerable::Repeat((Int32)0, _length));
		else if (_type == AxVariableType::axReal || _type == AxVariableType::axLongReal) _realValues = System::Linq::Enumerable::ToList(System::Linq::Enumerable::Repeat((Double)0, _length));
		else if (_type == AxVariableType::axString) _stringValues = System::Linq::Enumerable::ToList(System::Linq::Enumerable::Repeat(gcnew String(""), _length));
	}

	void AxVariable::GetType()
	{
		_ax->QueueInitFunction(Binder::Bind(gcnew NoParameterDelegate(this, &AxVariable::InvokeGetType)));
	}

	void AxVariable::InvokeGetRemark()
	{
		const char* result = AxGetRemark(_execData);
		if (result) _remark = gcnew String(result);
	}

	void AxVariable::GetRemark()
	{
		_ax->QueueInitFunction(Binder::Bind(gcnew NoParameterDelegate(this, &AxVariable::InvokeGetRemark)));
	}

	void AxVariable::InvokeGetLength()
	{
		_length = AxGetArrayCnt(_execData);
		if (_length > 1) _isArray = true;
		else if (_length == 0) _length = 1;
	}

	void AxVariable::GetLength()
	{
		_ax->QueueInitFunction(Binder::Bind(gcnew NoParameterDelegate(this, &AxVariable::InvokeGetLength)));
	}

	void AxVariable::InvokeGetFlags(ManualResetEvent^ resetEvent)
	{
		ResetEventLock resetEventGuard(resetEvent);
		if (_type == AxVariableType::axUndefined) return;
		_io = AxGetIOVarFlag(_execData) == 1;
		_notConnected = AxGetNcFlag(_execData) == 1;
		_retentive = AxGetRetentiveFlag(_execData) == 1;
		_constant = AxGetConstantFlag(_execData) == 1;
		_private = AxGetPrivateFlag(_execData) == 1;
		_local = AxGetLocalFlag(_execData) == 1;
		_configurationValue = AxGetConfValueFlag(_execData) == 1;
		_parameter = AxGetParameterFlag(_execData) == 1;
		_remote = AxGetRemoteFlag(_execData) == 1;

		AX_ATTR attrs;
		if (AxGetAttributes(_execData, &attrs) == -1) return;
		_decimalPoints = attrs.dec_point;
		if (attrs.dim) _dimension = gcnew String(attrs.dim);
		_global = attrs.rem != 0;
		_trending = attrs.trend != 0;
		_reloadComplete = true;
		_initResetEvent->Set();
	}

	void AxVariable::GetFlags(bool wait)
	{
		ManualResetEvent^ resetEvent = gcnew ManualResetEvent(false);
		_ax->QueueInitFunction(Binder::Bind(gcnew ResetEventDelegate(this, &AxVariable::InvokeGetFlags), resetEvent));
		if(wait) resetEvent->WaitOne();
	}
	//}}}

	//{{{ Queued synchronous methods
	void AxVariable::InvokeGetEnumText(ManualResetEvent^ resetEvent, Int32 enumIndex)
	{
		ResetEventLock resetEventGuard(resetEvent);
		if (!_execData || !AxVarIsEnum(_execData)) return;

		char buffer[51] = "";
		AxGetEnumText(_execData, enumIndex, buffer, 50);
		buffer[50] = 0;
		_enumTexts[enumIndex] = gcnew String(buffer);
	}

	String^ AxVariable::GetEnumText(Int32 enumIndex)
	{
		if (_enumTexts && _enumTexts->ContainsKey(enumIndex)) return _enumTexts[enumIndex];
		ManualResetEvent^ resetEvent = gcnew ManualResetEvent(false);
		_ax->QueueSynchronousFunction(Binder::Bind(gcnew OneIntegerParameterDelegate(this, &AxVariable::InvokeGetEnumText), resetEvent, enumIndex));
		resetEvent->WaitOne();
		if (_enumTexts && _enumTexts->ContainsKey(enumIndex)) return _enumTexts[enumIndex]; else return "";
	}
	//}}}

	void AxVariable::WaitForReloadCompleted()
	{
		if (!_reloadComplete) _initResetEvent->WaitOne();
	}

	List<UInt16>^ AxVariable::Pull()
	{
		List<UInt16>^ changedIndexes = gcnew List<UInt16>();
		if (!_execData || !_reloadComplete) return changedIndexes;
		struct tagAxVariant data;
		if (_type == AxVariableType::axBool || _type == AxVariableType::axAlarm)
		{
			bool changed = false;
			for (UInt16 i = 0; i < _length; i++)
			{
				if (_isArray) AxGetArray(_execData, &data, i); else AxGet(_execData, &data);
				if ((data.AXVAL.btBOOL != 0) != _boolValues[i])
				{
					_boolValues[i] = data.AXVAL.btBOOL != 0;
					changedIndexes->Add(i);
				}
			}
		}
		else if (_type == AxVariableType::axByte)
		{
			bool changed = false;
			for (UInt16 i = 0; i < _length; i++)
			{
				if (_isArray) AxGetArray(_execData, &data, i); else AxGet(_execData, &data);
				if ((char)data.AXVAL.btBYTE != _integerValues[i])
				{
					_integerValues[i] = (char)data.AXVAL.btBYTE;
					changedIndexes->Add(i);
				}
			}
		}
		else if (_type == AxVariableType::axUnsignedShortInteger)
		{
			bool changed = false;
			for (UInt16 i = 0; i < _length; i++)
			{
				if (_isArray) AxGetArray(_execData, &data, i); else AxGet(_execData, &data);
				if (data.AXVAL.btUSINT != _integerValues[i])
				{
					_integerValues[i] = data.AXVAL.btUSINT;
					changedIndexes->Add(i);
				}
			}
		}
		else if (_type == AxVariableType::axShortInteger)
		{
			bool changed = false;
			for (UInt16 i = 0; i < _length; i++)
			{
				if (_isArray) AxGetArray(_execData, &data, i); else AxGet(_execData, &data);
				if (data.AXVAL.btSINT != _integerValues[i])
				{
					_integerValues[i] = data.AXVAL.btSINT;
					changedIndexes->Add(i);
				}
			}
		}
		else if (_type == AxVariableType::axInteger)
		{
			bool changed = false;
			for (UInt16 i = 0; i < _length; i++)
			{
				if (_isArray) AxGetArray(_execData, &data, i); else AxGet(_execData, &data);
				if (data.AXVAL.btINT != _integerValues[i])
				{
					_integerValues[i] = data.AXVAL.btINT;
					changedIndexes->Add(i);
				}
			}
		}
		else if (_type == AxVariableType::axLongInteger)
		{
			bool changed = false;
			for (UInt16 i = 0; i < _length; i++)
			{
				if (_isArray) AxGetArray(_execData, &data, i); else AxGet(_execData, &data);
				if (data.AXVAL.btDINT != _integerValues[i])
				{
					_integerValues[i] = data.AXVAL.btDINT;
					changedIndexes->Add(i);
				}
			}
		}
		else if (_type == AxVariableType::axUnsignedInteger)
		{
			bool changed = false;
			for (UInt16 i = 0; i < _length; i++)
			{
				if (_isArray) AxGetArray(_execData, &data, i); else AxGet(_execData, &data);
				if (data.AXVAL.btUINT != _integerValues[i])
				{
					_integerValues[i] = data.AXVAL.btUINT;
					changedIndexes->Add(i);
				}
			}
		}
		else if (_type == AxVariableType::axUnsignedLongInteger)
		{
			bool changed = false;
			for (UInt16 i = 0; i < _length; i++)
			{
				if (_isArray) AxGetArray(_execData, &data, i); else AxGet(_execData, &data);
				if (data.AXVAL.btUDINT != _integerValues[i])
				{
					_integerValues[i] = data.AXVAL.btUDINT;
					changedIndexes->Add(i);
				}
			}
		}
		else if (_type == AxVariableType::axReal)
		{
			bool changed = false;
			for (UInt16 i = 0; i < _length; i++)
			{
				if (_isArray) AxGetArray(_execData, &data, i); else AxGet(_execData, &data);
				if (data.AXVAL.btREAL != (Single)_realValues[i])
				{
					_realValues[i] = (Single)data.AXVAL.btREAL;
					changedIndexes->Add(i);
				}
			}
		}
		else if (_type == AxVariableType::axLongReal)
		{
			bool changed = false;
			for (UInt16 i = 0; i < _length; i++)
			{
				if (_isArray) AxGetArray(_execData, &data, i); else AxGet(_execData, &data);
				if (data.AXVAL.btLREAL != _realValues[i])
				{
					_realValues[i] = data.AXVAL.btLREAL;
					changedIndexes->Add(i);
				}
			}
		}
		else if (_type == AxVariableType::axString)
		{
			bool changed = false;
			for (UInt16 i = 0; i < _length; i++)
			{
				if (_isArray) AxGetArray(_execData, &data, i); else AxGet(_execData, &data);
				String^ newValue = gcnew String(data.AXVAL.btSTRING);
				if (newValue != _stringValues[i])
				{
					_stringValues[i] = newValue;
					changedIndexes->Add(i);
				}
			}
		}
		if (!_initComplete)
		{
			_initComplete = true;
			return gcnew List<UInt16>();
		}
		return changedIndexes;
	}

	void AxVariable::Push()
	{
		if (!_execData || !_reloadComplete) return;
		if (_type == AxVariableType::axBool || _type == AxVariableType::axAlarm)
		{
			if (_isArray)
			{
				Lock changedIndexesGuard(_changedIndexesMutex);
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				for each (UInt16 index in _changedIndexes)
				{
					data.AXVAL.btBOOL = _boolValues[index];
					AxSetArray(_execData, &data, index);
				}
				_changedIndexes->Clear();
			}
			else
			{
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				data.AXVAL.btBOOL = _boolValues[0];
				AxSet(_execData, &data);
			}
		}
		else if (_type == AxVariableType::axByte)
		{
			if (_isArray)
			{
				Lock changedIndexesGuard(_changedIndexesMutex);
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				for each (UInt16 index in _changedIndexes)
				{
					data.AXVAL.btBYTE = (unsigned char)_integerValues[index];
					AxSetArray(_execData, &data, index);
				}
				_changedIndexes->Clear();
			}
			else
			{
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				data.AXVAL.btBYTE = (unsigned char)_integerValues[0];
				AxSet(_execData, &data);
			}
		}
		else if (_type == AxVariableType::axUnsignedShortInteger)
		{
			if (_isArray)
			{
				Lock changedIndexesGuard(_changedIndexesMutex);
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				for each (UInt16 index in _changedIndexes)
				{
					data.AXVAL.btUSINT = (unsigned char)_integerValues[index];
					AxSetArray(_execData, &data, index);
				}
				_changedIndexes->Clear();
			}
			else
			{
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				data.AXVAL.btUSINT = (unsigned char)_integerValues[0];
				AxSet(_execData, &data);
			}
		}
		else if (_type == AxVariableType::axShortInteger)
		{
			if (_isArray)
			{
				Lock changedIndexesGuard(_changedIndexesMutex);
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				for each (UInt16 index in _changedIndexes)
				{
					data.AXVAL.btSINT = (char)_integerValues[index];
					AxSetArray(_execData, &data, index);
				}
				_changedIndexes->Clear();
			}
			else
			{
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				data.AXVAL.btSINT = (char)_integerValues[0];
				AxSet(_execData, &data);
			}
		}
		else if (_type == AxVariableType::axInteger)
		{
			if (_isArray)
			{
				Lock changedIndexesGuard(_changedIndexesMutex);
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				for each (UInt16 index in _changedIndexes)
				{
					data.AXVAL.btINT = (Int16)_integerValues[index];
					AxSetArray(_execData, &data, index);
				}
				_changedIndexes->Clear();
			}
			else
			{
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				data.AXVAL.btINT = (Int16)_integerValues[0];
				AxSet(_execData, &data);
			}
		}
		else if (_type == AxVariableType::axLongInteger)
		{
			if (_isArray)
			{
				Lock changedIndexesGuard(_changedIndexesMutex);
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				for each (UInt16 index in _changedIndexes)
				{
					data.AXVAL.btDINT = _integerValues[index];
					AxSetArray(_execData, &data, index);
				}
				_changedIndexes->Clear();
			}
			else
			{
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				data.AXVAL.btDINT = _integerValues[0];
				AxSet(_execData, &data);
			}
		}
		else if (_type == AxVariableType::axUnsignedInteger)
		{
			if (_isArray)
			{
				Lock changedIndexesGuard(_changedIndexesMutex);
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				for each (UInt16 index in _changedIndexes)
				{
					data.AXVAL.btUINT = (UInt16)_integerValues[index];
					AxSetArray(_execData, &data, index);
				}
				_changedIndexes->Clear();
			}
			else
			{
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				data.AXVAL.btUINT = (UInt16)_integerValues[0];
				AxSet(_execData, &data);
			}
		}
		else if (_type == AxVariableType::axUnsignedLongInteger)
		{
			if (_isArray)
			{
				Lock changedIndexesGuard(_changedIndexesMutex);
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				for each (UInt16 index in _changedIndexes)
				{
					data.AXVAL.btUDINT = (UInt32)_integerValues[index];
					AxSetArray(_execData, &data, index);
				}
				_changedIndexes->Clear();
			}
			else
			{
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				data.AXVAL.btUDINT = (UInt32)_integerValues[0];
				AxSet(_execData, &data);
			}
		}
		else if (_type == AxVariableType::axReal)
		{
			if (_isArray)
			{
				Lock changedIndexesGuard(_changedIndexesMutex);
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				for each (UInt16 index in _changedIndexes)
				{
					data.AXVAL.btREAL = (Single)_realValues[index];
					AxSetArray(_execData, &data, index);
				}
				_changedIndexes->Clear();
			}
			else
			{
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				data.AXVAL.btREAL = (Single)_realValues[0];
				AxSet(_execData, &data);
			}
		}
		else if (_type == AxVariableType::axLongReal)
		{
			if (_isArray)
			{
				Lock changedIndexesGuard(_changedIndexesMutex);
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				for each (UInt16 index in _changedIndexes)
				{
					data.AXVAL.btLREAL = _realValues[index];
					AxSetArray(_execData, &data, index);
				}
				_changedIndexes->Clear();
			}
			else
			{
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				data.AXVAL.btLREAL = _realValues[0];
				AxSet(_execData, &data);
			}
		}
		else if (_type == AxVariableType::axString)
		{
			if (_isArray)
			{
				Lock changedIndexesGuard(_changedIndexesMutex);
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				for each (UInt16 index in _changedIndexes)
				{
					strcpy_s(data.AXVAL.btSTRING, _converter.GetString(_stringValues[index]).c_str());
					AxSetArray(_execData, &data, index);
				}
				_changedIndexes->Clear();
			}
			else
			{
				struct tagAxVariant data;
				data.ucVarType = (unsigned char)_type;
				strcpy_s(data.AXVAL.btSTRING, _converter.GetString(_stringValues[0]).c_str());
				AxSet(_execData, &data);
			}
		}

		_changed = false;
	}

	//{{{ BOOL
		bool AxVariable::GetBool()
		{
			if (_type != AxVariableType::axBool && _type != AxVariableType::axAlarm) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type BOOL.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			return _boolValues[0];
		}

		bool AxVariable::GetBool(UInt16 index)
		{
			if (_type != AxVariableType::axBool && _type != AxVariableType::axAlarm) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type BOOL.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			return _boolValues[index];
		}

		void AxVariable::Set(bool value)
		{
			if (_type != AxVariableType::axBool && _type != AxVariableType::axAlarm) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type BOOL.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			_boolValues[0] = value;
			_changed = true;
		}

		void AxVariable::Set(UInt16 index, bool value)
		{
			if (_type != AxVariableType::axBool && _type != AxVariableType::axAlarm) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type BOOL.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			if (index >= _length) throw gcnew AxArrayIndexOutOfRangeException("Index for variable " + _path + " is out of range (" + index.ToString() + " >= " + _length.ToString() + ").");
			_boolValues[index] = value;
			_changed = true;
			Lock changedIndexesGuard(_changedIndexesMutex);
			_changedIndexes->Add(index);
		}
	//}}}

	//{{{ BYTE
		char AxVariable::GetByte()
		{
			if (_type != AxVariableType::axByte) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type BYTE.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			return (unsigned char)_integerValues[0];
		}

		char AxVariable::GetByte(UInt16 index)
		{
			if (_type != AxVariableType::axByte) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type BYTE.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			return (unsigned char)_integerValues[index];
		}

		void AxVariable::Set(char value)
		{
			if (_type != AxVariableType::axByte && _type != AxVariableType::axShortInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type BYTE or SINT.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			_integerValues[0] = value;
			_changed = true;
		}

		void AxVariable::Set(UInt16 index, char value)
		{
			if (_type != AxVariableType::axByte && _type != AxVariableType::axShortInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type BYTE or SINT.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			if (index >= _length) throw gcnew AxArrayIndexOutOfRangeException("Index for variable " + _path + " is out of range (" + index.ToString() + " >= " + _length.ToString() + ").");
			_integerValues[index] = value;
			_changed = true;
			Lock changedIndexesGuard(_changedIndexesMutex);
			_changedIndexes->Add(index);
		}
	//}}}

	//{{{ USINT
		Byte AxVariable::GetUnsignedShortInteger()
		{
			if (_type != AxVariableType::axUnsignedShortInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type USINT.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			return (unsigned char)_integerValues[0];
		}

		Byte AxVariable::GetUnsignedShortInteger(UInt16 index)
		{
			if (_type != AxVariableType::axUnsignedShortInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type USINT.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			return (unsigned char)_integerValues[index];
		}

		void AxVariable::Set(Byte value)
		{
			if (_type != AxVariableType::axUnsignedShortInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type USINT.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			_integerValues[0] = value;
			_changed = true;
		}

		void AxVariable::Set(UInt16 index, Byte value)
		{
			if (_type != AxVariableType::axUnsignedShortInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type USINT.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			if (index >= _length) throw gcnew AxArrayIndexOutOfRangeException("Index for variable " + _path + " is out of range (" + index.ToString() + " >= " + _length.ToString() + ").");
			_integerValues[index] = value;
			_changed = true;
			Lock changedIndexesGuard(_changedIndexesMutex);
			_changedIndexes->Add(index);
		}
	//}}}

	//{{{ SINT
		char AxVariable::GetShortInteger()
		{
			if (_type != AxVariableType::axShortInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type SINT.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			return (unsigned char)_integerValues[0];
		}

		char AxVariable::GetShortInteger(UInt16 index)
		{
			if (_type != AxVariableType::axShortInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type SINT.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			return (unsigned char)_integerValues[index];
		}
	//}}}

	//{{{ INT
		Int16 AxVariable::GetInteger()
		{
			if (_type != AxVariableType::axInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type INT.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			return (Int16)_integerValues[0];
		}

		Int16 AxVariable::GetInteger(UInt16 index)
		{
			if (_type != AxVariableType::axInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type INT.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			return (Int16)_integerValues[index];
		}

		void AxVariable::Set(Int16 value)
		{
			if (_type != AxVariableType::axInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type INT.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			_integerValues[0] = value;
			_changed = true;
		}

		void AxVariable::Set(UInt16 index, Int16 value)
		{
			if (_type != AxVariableType::axInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type INT.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			if (index >= _length) throw gcnew AxArrayIndexOutOfRangeException("Index for variable " + _path + " is out of range (" + index.ToString() + " >= " + _length.ToString() + ").");
			_integerValues[index] = value;
			_changed = true;
			Lock changedIndexesGuard(_changedIndexesMutex);
			_changedIndexes->Add(index);
		}
	//}}}

	//{{{ DINT
		Int32 AxVariable::GetLongInteger()
		{
			if (_type != AxVariableType::axLongInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type DINT.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			return _integerValues[0];
		}

		Int32 AxVariable::GetLongInteger(UInt16 index)
		{
			if (_type != AxVariableType::axLongInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type DINT.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			return _integerValues[index];
		}

		void AxVariable::Set(Int32 value)
		{
			if (_type != AxVariableType::axLongInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type DINT.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			_integerValues[0] = value;
			_changed = true;
		}

		void AxVariable::Set(UInt16 index, Int32 value)
		{
			if (_type != AxVariableType::axLongInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type DINT.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			if (index >= _length) throw gcnew AxArrayIndexOutOfRangeException("Index for variable " + _path + " is out of range (" + index.ToString() + " >= " + _length.ToString() + ").");
			_integerValues[index] = value;
			_changed = true;
			Lock changedIndexesGuard(_changedIndexesMutex);
			_changedIndexes->Add(index);
		}
	//}}}

	//{{{ UINT
		UInt16 AxVariable::GetUnsignedInteger()
		{
			if (_type != AxVariableType::axUnsignedInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type UINT.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			return (UInt16)_integerValues[0];
		}

		UInt16 AxVariable::GetUnsignedInteger(UInt16 index)
		{
			if (_type != AxVariableType::axUnsignedInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type UINT.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			return (UInt16)_integerValues[index];
		}

		void AxVariable::Set(UInt16 value)
		{
			if (_type != AxVariableType::axUnsignedInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type UINT.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			_integerValues[0] = value;
			_changed = true;
		}

		void AxVariable::Set(UInt16 index, UInt16 value)
		{
			if (_type != AxVariableType::axUnsignedInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type UINT.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			if (index >= _length) throw gcnew AxArrayIndexOutOfRangeException("Index for variable " + _path + " is out of range (" + index.ToString() + " >= " + _length.ToString() + ").");
			_integerValues[index] = value;
			_changed = true;
			Lock changedIndexesGuard(_changedIndexesMutex);
			_changedIndexes->Add(index);
		}
	//}}}

	//{{{ UDINT
		UInt32 AxVariable::GetUnsignedLongInteger()
		{
			if (_type != AxVariableType::axUnsignedLongInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type UDINT.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			return (UInt32)_integerValues[0];
		}

		UInt32 AxVariable::GetUnsignedLongInteger(UInt16 index)
		{
			if (_type != AxVariableType::axUnsignedLongInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type UDINT.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			return (UInt32)_integerValues[index];
		}

		void AxVariable::Set(UInt32 value)
		{
			if (_type != AxVariableType::axUnsignedLongInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type UDINT.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			_integerValues[0] = value;
			_changed = true;
		}

		void AxVariable::Set(UInt16 index, UInt32 value)
		{
			if (_type != AxVariableType::axUnsignedLongInteger) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type UDINT.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			if (index >= _length) throw gcnew AxArrayIndexOutOfRangeException("Index for variable " + _path + " is out of range (" + index.ToString() + " >= " + _length.ToString() + ").");
			_integerValues[index] = value;
			_changed = true;
			Lock changedIndexesGuard(_changedIndexesMutex);
			_changedIndexes->Add(index);
		}
	//}}}

	//{{{ REAL
		Single AxVariable::GetReal()
		{
			if (_type != AxVariableType::axReal) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type REAL.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			return (Single)_realValues[0];
		}

		Single AxVariable::GetReal(UInt16 index)
		{
			if (_type != AxVariableType::axReal) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type REAL.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			return (Single)_realValues[index];
		}

		void AxVariable::Set(Single value)
		{
			if (_type != AxVariableType::axReal) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type REAL.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			_realValues[0] = value;
			_changed = true;
		}

		void AxVariable::Set(UInt16 index, Single value)
		{
			if (_type != AxVariableType::axReal) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type REAL.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			if (index >= _length) throw gcnew AxArrayIndexOutOfRangeException("Index for variable " + _path + " is out of range (" + index.ToString() + " >= " + _length.ToString() + ").");
			_realValues[index] = value;
			_changed = true;
			Lock changedIndexesGuard(_changedIndexesMutex);
			_changedIndexes->Add(index);
		}
	//}}}

	//{{{ LREAL
		Double AxVariable::GetLongReal()
		{
			if (_type != AxVariableType::axLongReal) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type LREAL.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			return _realValues[0];
		}

		Double AxVariable::GetLongReal(UInt16 index)
		{
			if (_type != AxVariableType::axLongReal) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type LREAL.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			return _realValues[index];
		}

		void AxVariable::Set(Double value)
		{
			if (_type != AxVariableType::axLongReal) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type LREAL.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			_realValues[0] = value;
			_changed = true;
		}

		void AxVariable::Set(UInt16 index, Double value)
		{
			if (_type != AxVariableType::axLongReal) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type LREAL.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			if (index >= _length) throw gcnew AxArrayIndexOutOfRangeException("Index for variable " + _path + " is out of range (" + index.ToString() + " >= " + _length.ToString() + ").");
			_realValues[index] = value;
			_changed = true;
			Lock changedIndexesGuard(_changedIndexesMutex);
			_changedIndexes->Add(index);
		}
	//}}}

	//{{{ STRING
		String^ AxVariable::GetString()
		{
			if (_type != AxVariableType::axString) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type STRING.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			return _stringValues[0];
		}

		String^ AxVariable::GetString(UInt16 index)
		{
			if (_type != AxVariableType::axString) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type STRING.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			return _stringValues[index];
		}

		void AxVariable::Set(String^ value)
		{
			if (_type != AxVariableType::axString) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type STRING.");
			if (_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is an array. Please specify the element index.");
			if (value->Length > 1023) value = value->Substring(0, 1023);
			_stringValues[0] = value;
			_changed = true;
		}

		void AxVariable::Set(UInt16 index, String^ value)
		{
			if (_type != AxVariableType::axString) throw gcnew AxVariableTypeException("Variable " + _path + " is not of type STRING.");
			if (!_isArray) throw gcnew AxVariableTypeException("Variable " + _path + " is no array.");
			if (index >= _length) throw gcnew AxArrayIndexOutOfRangeException("Index for variable " + _path + " is out of range (" + index.ToString() + " >= " + _length.ToString() + ").");
			if (value->Length > 1023) value = value->Substring(0, 1023);
			_stringValues[index] = value;
			_changed = true;
			Lock changedIndexesGuard(_changedIndexesMutex);
			_changedIndexes->Add(index);
		}
	//}}}
}