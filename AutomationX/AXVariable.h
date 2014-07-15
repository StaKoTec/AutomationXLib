#pragma once

#include "axsapi32.h"
#include "ManagedTypeConverter.h"

namespace AutomationX
{
	ref class AXInstance;

	public enum class AXVariableType { axBool = 2, axByte = 3, axInteger = 6, axLongInteger = 8, axUnsignedInteger = 7, axUnsignedLongInteger = 9, axReal = 10, axString = 13 };

	public ref class AXVariable
	{
	private:
		bool _isArray = false;
		AX^ _ax;
		ManagedTypeConverter _converter;
		AXInstance^ _instance;
		char* _cName = nullptr;
		String^ _name = "";
		AXVariableType _type;
		UInt16 _length = 1;

		List<bool>^ _boolValues = nullptr;
		List<Int64>^ _integerValues = nullptr;
		List<Single>^ _realValues = nullptr;
		List<String^>^ _stringValues = nullptr;

		int GetRawType();
		void Set(tagAxVariant& data, UInt16 index);
	public:
		delegate void ValueChangedEventHandler(AXVariable^ sender);
		delegate void ArrayValueChangedEventHandler(AXVariable^ sender, UInt16 index);

		/// <summary>Fired when the value of the variable is changed in aX. Only raised, after "EnableVariableEvents" has been called on the variable's instance object or after manually calling "Refresh".</summary>
		event ValueChangedEventHandler^ OnValueChanged;
		/// <summary>Fired when the value of an array element is changed in aX. Only raised, after "EnableVariableEvents" has been called on the variable's instance object or after manually calling "Refresh".</summary>
		event ArrayValueChangedEventHandler^ OnArrayValueChanged;

		/// <summary>Returns the aX object of the variable.</summary>
		property AX^ AutomationX { AX^ get() { return _ax; } }

		/// <summary>Returns the instance of the variable.</summary>
		property AXInstance^ Instance { AXInstance^ get() { return _instance; } }

		/// <summary>Returns the name of the variable.</summary>
		property String^ Name { String^ get() { return _name; } }

		/// <summary>Returns the type of the variable.</summary>
		property AXVariableType Type { AXVariableType get() { return _type; } }
		
		/// <summary>Returns the name of the variable's reference.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		property String^ ReferenceName { String^ get(); }

		/// <summary>Returns the remark of the variable</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		property String^ Remark { String^ get(); }

		/// <summary>Determine if the variable is part of an array.</summary>
		property bool IsArray { bool get() { return _isArray; } }

		/// <summary>Returns the length of the array.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is no array.</exception>
		property UInt16 Length { UInt16 get(); }

		/// <summary>Gets the number of decimal places of a variable of type REAL.</summary>
		/// <exception cref="AXVariableException">Thrown when variable was not found.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type REAL.</exception>
		property Int32 DecimalPoints { Int32 get(); }

		/// <summary>Concstructor.</summary>
		/// <param name="instance">The instance the variable belongs to.</param>
		/// <param name="name">The name of the variable.</param>
		/// <exception cref="AXVariableException">Thrown when variable was not found or on handle errors.</exception>
		AXVariable(AXInstance^ instance, String^ name);

		virtual ~AXVariable();

		/// <summary>Clears all stored values.</summary>
		void Clear();

		/// <summary>Reads all values from aX.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		void Refresh();

		/// <summary>Reads all values from aX.</summary>
		/// <param name="raiseEvents">If set to "true", "OnValueChanged" or "OnArrayValueChanged" will be raised when the variable was changed.</param>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		void Refresh(bool raiseEvents);

		/// <summary>Reads one value from aX.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		void Refresh(UInt16 index);

		/// <summary>Reads one value from aX.</summary>
		/// <param name="raiseEvents">If set to "true", "OnValueChanged" or "OnArrayValueChanged" will be raised when an array element was changed.</param>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		void Refresh(UInt16 index, bool raiseEvents);

		/// <summary>Gets the value of a variable of type BOOL.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type BOOL.</exception>
		bool GetBool();
		
		/// <summary>Sets the value of a variable of type BOOL.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type BOOL.</exception>
		void Set(bool value);

		/// <summary>Gets the value of an array element of type BOOL.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type BOOL.</exception>
		bool GetBool(UInt16 index);

		/// <summary>Sets the value of an array element of type BOOL.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type BOOL.</exception>
		void Set(UInt16 index, bool value);

		/// <summary>Gets the value of a variable of type BYTE.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type BYTE.</exception>
		Byte GetByte();

		/// <summary>Sets the value of a variable of type BYTE.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type BYTE.</exception>
		void Set(Byte value);

		/// <summary>Gets the value of an array element of type BYTE.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type BYTE.</exception>
		Byte GetByte(UInt16 index);

		/// <summary>Sets the value of an array element of type BYTE.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type BYTE.</exception>
		void Set(UInt16 index, Byte value);

		/// <summary>Gets the value of a variable of type INT.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type INT.</exception>
		Int16 GetInteger();

		/// <summary>Sets the value of a variable of type INT.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type INT.</exception>
		void Set(Int16 value);

		/// <summary>Gets the value of an array element of type INT.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type INT.</exception>
		Int16 GetInteger(UInt16 index);

		/// <summary>Sets the value of an array element of type INT.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type INT.</exception>
		void Set(UInt16 index, Int16 value);

		/// <summary>Gets the value of a variable of type DINT.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type DINT.</exception>
		Int32 GetLongInteger();

		/// <summary>Sets the value of a variable of type DINT.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type DINT.</exception>
		void Set(Int32 value);

		/// <summary>Gets the value of an array element of type DINT.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type DINT.</exception>
		Int32 GetLongInteger(UInt16 index);

		/// <summary>Sets the value of an array element of type DINT.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type DINT.</exception>
		void Set(UInt16 index, Int32 value);

		/// <summary>Gets the value of a variable of type UINT.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type UINT.</exception>
		UInt16 GetUnsignedInteger();

		/// <summary>Sets the value of a variable of type UINT.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type UINT.</exception>
		void Set(UInt16 value);

		/// <summary>Gets the value of an array element of type UINT.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type UINT.</exception>
		UInt16 GetUnsignedInteger(UInt16 index);

		/// <summary>Sets the value of an array element of type UINT.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type UINT.</exception>
		void Set(UInt16 index, UInt16 value);

		/// <summary>Gets the value of a variable of type UDINT.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type UDINT.</exception>
		UInt32 GetUnsignedLongInteger();

		/// <summary>Sets the value of a variable of type UDINT.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type UDINT.</exception>
		void Set(UInt32 value);

		/// <summary>Gets the value of an array element of type UDINT.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type UDINT.</exception>
		UInt32 GetUnsignedLongInteger(UInt16 index);

		/// <summary>Sets the value of an array element of type UDINT.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type UDINT.</exception>
		void Set(UInt16 index, UInt32 value);

		/// <summary>Gets the value of a variable of type REAL.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type REAL.</exception>
		Single GetReal();

		/// <summary>Sets the value of a variable of type REAL.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type REAL.</exception>
		void Set(Single value);

		/// <summary>Gets the value of an array element of type REAL.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type REAL.</exception>
		Single GetReal(UInt16 index);

		/// <summary>Sets the value of an array element of type REAL.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type REAL.</exception>
		void Set(UInt16 index, Single value);

		/// <summary>Gets the value of a variable of type STRING.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type STRING.</exception>
		String^ GetString();

		/// <summary>Sets the value of a variable of type STRING.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type STRING.</exception>
		void Set(String^ value);

		/// <summary>Gets the value of an array element of type STRING.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type STRING.</exception>
		String^ GetString(UInt16 index);

		/// <summary>Sets the value of an array element of type STRING.</summary>
		/// <exception cref="AXVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AXVariableTypeException">Thrown when variable is not of type STRING.</exception>
		void Set(UInt16 index, String^ value);
	};

}
