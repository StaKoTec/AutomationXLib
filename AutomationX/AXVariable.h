#pragma once

using namespace System;
using namespace System::Collections::Generic;

#include "axsapi32.h"
#include "ManagedTypeConverter.h"
#include "AxVariableValue.h"

namespace AutomationX
{
	ref class AxInstance;
	ref class Ax;
	ref class AxVariable;

	public enum class AxVariableDeclaration
	{
		axUndefined = -1,
		axVar = 0,
		axVarInput = 1,
		axVarOutput = 2,
		axVarInputOutput = 3,
		axVarExternal = 4,
		axVarGlobal = 5
	};

	public ref class AxVariableEventData
	{
	public:
		UInt16 Index = 0;
		AxVariable^ Variable = nullptr;
		AxVariableValue^ Value = nullptr;
		DateTime Timestamp;

		AxVariableEventData() {}

		AxVariableEventData(AxVariable^ variable, UInt16 index, AxVariableValue^ value, DateTime timestamp) : Variable(variable), Index(index), Value(value), Timestamp(timestamp) {}

		virtual ~AxVariableEventData()
		{
			this->!AxVariableEventData();
		}

		!AxVariableEventData()
		{
			Variable = nullptr;
			Value = nullptr;
		}
	};

	public ref class AxVariable : IDisposable
	{
	private:
		void* _execData = nullptr;
		ManagedTypeConverter _converter;
		Ax^ _ax = nullptr;
		char* _cName = nullptr;

		UInt32 _pollId = 0;
		bool _reloadComplete = false;
		ManualResetEvent^ _initResetEvent = gcnew ManualResetEvent(false);
		bool _initComplete = false;

		// {{{ Properties
		Object^ _eventsMutex = gcnew Object();
		bool _events = false;
		bool _cleanUp = false;
		AxInstance^ _instance = nullptr;
		String^ _name = "";
		String^ _path = "";
		String^ _referenceName = "";
		AxVariableDeclaration _declaration = AxVariableDeclaration::axVar;
		AxVariableType _type = AxVariableType::axUndefined;
		String^ _remark = "";
		bool _isArray = false;
		UInt16 _length = 1;
		Int32 _decimalPoints = 0;
		String^ _dimension = "";
		bool _io = false;
		bool _notConnected = false;
		bool _global = false;
		bool _trending = false;
		bool _retentive = false;
		bool _constant = false;
		bool _private = false;
		bool _local = false;
		bool _configurationValue = false;
		bool _parameter = false;
		bool _remote = false;
		Object^ _changedMutex = gcnew Object();
		bool _changed = false;
		Object^ _changedIndexesMutex = gcnew Object();
		List<UInt16>^ _changedIndexes = gcnew List<UInt16>();
		Object^ _pullMutex = gcnew Object();
		// }}}

		Dictionary<Int32, String^>^ _enumTexts = nullptr;
		List<bool>^ _boolValues = nullptr;
		List<Int32>^ _integerValues = nullptr;
		List<Double>^ _realValues = nullptr;
		List<String^>^ _stringValues = nullptr;

		void GetExecData();

		//{{{ Queued init methods
		delegate void NoParameterDelegate();
		delegate void ResetEventDelegate(ManualResetEvent^ resetEvent);

		void InvokeGetReferenceName();
		void GetReferenceName();
		void InvokeGetDeclaration();
		void GetDeclaration();
		void InvokeGetType();
		void GetType();
		void InvokeGetRemark();
		void GetRemark();
		void InvokeGetLength();
		void GetLength();
		void InvokeGetFlags(ManualResetEvent^ resetEvent);
		void GetFlags(bool wait);
		//}}}

		//{{{ Queued synchronous methods
		delegate void OneIntegerParameterDelegate(ManualResetEvent^ resetEvent, Int32 integer);

		void InvokeGetEnumText(ManualResetEvent^ resetEvent, Int32 enumIndex);
		//}}}
	internal:

		/* Before making the constructor public, all references to AxVariable need to be removed from the Ax class. */
		/// <summary>Concstructor.</summary>
		/// <param name="instance">The instance the variable belongs to.</param>
		/// <param name="name">The name of the variable.</param>
		/// <exception cref="AxVariableException">Thrown when variable was not found or on handle errors.</exception>
		AxVariable(AxInstance^ instance, String^ name);

		List<UInt16>^ Pull();
		void Push();
		void RaiseValueChanged(AxVariableValue^ value, DateTime timestamp);
		void RaiseArrayValueChanged(UInt16 index, AxVariableValue^ value, DateTime timestamp);
		void ReloadStaticProperties(bool wait);
		void WaitForReloadCompleted();
		void SetCleanUp() { _cleanUp = true; }
		bool SpsIdChanged();
		void LockPullMutex() { Monitor::Enter(_pullMutex); }
		void UnlockPullMutex() { Monitor::Exit(_pullMutex); }
	public:
		delegate void ValueChangedEventHandler(AxVariable^ sender, AxVariableValue^ value, DateTime timestamp);
		delegate void ArrayValueChangedEventHandler(AxVariable^ sender, UInt16 index, AxVariableValue^ value, DateTime timestamp);

		/// <summary>Fired when the value of the variable is changed in aX. Only raised, after "EnableVariableEvents" has been called on the variable's instance object or after manually calling "Refresh".</summary>
		event ValueChangedEventHandler^ ValueChanged;

		/// <summary>Fired when the value of an array element is changed in aX. Only raised, after "EnableVariableEvents" has been called on the variable's instance object or after manually calling "Refresh".</summary>
		event ArrayValueChangedEventHandler^ ArrayValueChanged;

		/// <summary>Returns true if the variable does not exist anymore.</summary>
		property bool CleanUp { bool get() { return _cleanUp; } }

		/// <summary>Set to true to enable checking this variable for changes.</summary>
		property bool Events { bool get(); void set(bool value); }

		/// <summary>Returns the instance of the variable.</summary>
		property AxInstance^ Instance { AxInstance^ get() { return _instance; } }

		/// <summary>Returns the name of the variable.</summary>
		property String^ Name { String^ get() { return _name; } }

		/// <summary>Returns the full path of the variable including all instance names separated by ".".</summary>
		property String^ Path { String^ get(); }

		/// <summary>Returns the type of the variable.</summary>
		property AxVariableType Type { AxVariableType get() { return _type; } }

		/// <summary>Returns the name of the variable's reference.</summary>
		property String^ ReferenceName { String^ get() { return _referenceName; } }

		/// <summary>Returns the declaration of the variable (VAR, VAR_INPUT, VAR_OUTPUT, VAR_IN_OUT, VAR_EXTERNAL or VAR_GLOBAL).</summary>
		property AxVariableDeclaration Declaration { AxVariableDeclaration get() { return _declaration; } }

		/// <summary>Returns or sets the remark of the variable</summary>
		property String^ Remark { String^ get() { return _remark; }; }

		/// <summary>Determine if the variable is part of an array.</summary>
		property bool IsArray { bool get() { return _isArray; } }

		/// <summary>Returns the length of the array.</summary>
		property UInt16 Length { UInt16 get() { return _length; } }

		/// <summary>Gets the number of decimal places of a variable of type REAL.</summary>
		property Int32 DecimalPoints { Int32 get() { return _type == AxVariableType::axReal ? _decimalPoints : 0; } }

		/// <summary>Gets the dimension of a variable.</summary>
		property String^ Dimension { String^ get() { return _dimension; } }

		/// <summary>Determine if the variable is an IO variable.</summary>
		property bool Io { bool get() { return _io; } }

		/// <summary>Determine if the not connected flag is set.</summary>
		property bool NotConnected { bool get() { return _notConnected; } }

		/// <summary>Determine if the variable is a global variable.</summary>
		property bool Global { bool get() { return _global; } }

		/// <summary>Determine if the trending flag is set.</summary>
		property bool Trending { bool get() { return _trending; } }

		/// <summary>Determine if the retentive flag is set.</summary>
		property bool Retentive { bool get() { return _retentive; } }

		/// <summary>Determine if the constant flag is set.</summary>
		property bool Constant { bool get() { return _constant; } }

		/// <summary>Determine if the private flag is set.</summary>
		property bool Private { bool get() { return _private; } }

		/// <summary>Determine if the local flag is set.</summary>
		property bool Local { bool get() { return _local; } }

		/// <summary>Determine if the configuration value flag is set.</summary>
		property bool ConfigurationValue { bool get() { return _configurationValue; } }

		/// <summary>Determine if the parameter flag is set.</summary>
		property bool Parameter { bool get() { return _parameter; } }

		/// <summary>Determine if the remote flag is set.</summary>
		property bool Remote { bool get() { return _remote; } }

		property bool ReloadComplete { bool get() { return _reloadComplete; } }

		property bool Changed { bool get() { Lock changedGuard(_changedMutex); return _changed; } }

		property List<UInt16>^ ChangedIndexes { List<UInt16>^ get() { return _changedIndexes; } }

		virtual ~AxVariable();
		!AxVariable();

		/// <summary>Gets the value of a variable.</summary>
		/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
		AxVariableValue^ GetValue();

		/// <summary>Gets the value of an array element.</summary>
		/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
		AxVariableValue^ GetValue(UInt16 index);

		/// <summary>Gets the value of a variable of type BOOL.</summary>
		/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AxVariableTypeException">Thrown when variable is not of type BOOL.</exception>
		bool GetBool();

		/// <summary>Gets the value of an array element of type BOOL.</summary>
		/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AxVariableTypeException">Thrown when variable is not of type BOOL.</exception>
		bool GetBool(UInt16 index);

		/// <summary>Sets the value of a variable of type BOOL.</summary>
		/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AxVariableTypeException">Thrown when variable is not of type BOOL.</exception>
		void Set(bool value);

		/// <summary>Sets the value of an array element of type BOOL.</summary>
		/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AxVariableTypeException">Thrown when variable is not of type BOOL.</exception>
		void Set(UInt16 index, bool value);

		/// <summary>Gets the value of a variable of type BYTE.</summary>
		/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AxVariableTypeException">Thrown when variable is not of type BYTE.</exception>
		char GetByte();

		/// <summary>Gets the value of an array element of type BYTE.</summary>
		/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AxVariableTypeException">Thrown when variable is not of type BYTE.</exception>
		char GetByte(UInt16 index);

		/// <summary>Sets the value of a variable of type BYTE.</summary>
		/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AxVariableTypeException">Thrown when variable is not of type BYTE.</exception>
		void Set(char value);

		/// <summary>Sets the value of an array element of type BYTE.</summary>
		/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AxVariableTypeException">Thrown when variable is not of type BYTE.</exception>
		void Set(UInt16 index, char value);

		/// <summary>Gets the value of a variable of type USINT.</summary>
		/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AxVariableTypeException">Thrown when variable is not of type USINT.</exception>
		Byte GetUnsignedShortInteger();

		/// <summary>Gets the value of an array element of type USINT.</summary>
		/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AxVariableTypeException">Thrown when variable is not of type USINT.</exception>
		Byte GetUnsignedShortInteger(UInt16 index);

		/// <summary>Sets the value of a variable of type USINT.</summary>
		/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AxVariableTypeException">Thrown when variable is not of type USINT.</exception>
		void Set(Byte value);

		/// <summary>Sets the value of an array element of type USINT.</summary>
		/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AxVariableTypeException">Thrown when variable is not of type USINT.</exception>
		void Set(UInt16 index, Byte value);

		/// <summary>Gets the value of a variable of type SINT.</summary>
		/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AxVariableTypeException">Thrown when variable is not of type SINT.</exception>
		char GetShortInteger();

		/// <summary>Gets the value of an array element of type SINT.</summary>
		/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
		/// <exception cref="AxVariableTypeException">Thrown when variable is not of type SINT.</exception>
		char GetShortInteger(UInt16 index);

		//{{{ INT
			/// <summary>Gets the value of a variable of type INT.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type INT.</exception>
			Int16 GetInteger();

			/// <summary>Gets the value of an array element of type INT.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type INT.</exception>
			Int16 GetInteger(UInt16 index);

			/// <summary>Sets the value of a variable of type INT.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type INT.</exception>
			void Set(Int16 value);

			/// <summary>Sets the value of an array element of type INT.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type INT.</exception>
			void Set(UInt16 index, Int16 value);
		//}}}

		//{{{ DINT
			/// <summary>Gets the value of a variable of type DINT.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type DINT.</exception>
			Int32 GetLongInteger();

			/// <summary>Gets the value of an array element of type DINT.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type DINT.</exception>
			Int32 GetLongInteger(UInt16 index);

			/// <summary>Sets the value of a variable of type DINT.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type DINT.</exception>
			void Set(Int32 value);

			/// <summary>Sets the value of an array element of type DINT.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type DINT.</exception>
			void Set(UInt16 index, Int32 value);
		//}}}

		//{{{ UINT
			/// <summary>Gets the value of a variable of type UINT.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type UINT.</exception>
			UInt16 GetUnsignedInteger();

			/// <summary>Gets the value of an array element of type UINT.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type UINT.</exception>
			UInt16 GetUnsignedInteger(UInt16 index);

			/// <summary>Sets the value of a variable of type UINT.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type UINT.</exception>
			void Set(UInt16 value);

			/// <summary>Sets the value of an array element of type UINT.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type UINT.</exception>
			void Set(UInt16 index, UInt16 value);
		//}}}

		//{{{ UDINT
			/// <summary>Gets the value of a variable of type UDINT.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type UDINT.</exception>
			UInt32 GetUnsignedLongInteger();

			/// <summary>Gets the value of an array element of type UDINT.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type UDINT.</exception>
			UInt32 GetUnsignedLongInteger(UInt16 index);

			/// <summary>Sets the value of a variable of type UDINT.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type UDINT.</exception>
			void Set(UInt32 value);

			/// <summary>Sets the value of an array element of type UDINT.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type UDINT.</exception>
			void Set(UInt16 index, UInt32 value);
		//}}}

		//{{{ REAL
			/// <summary>Gets the value of a variable of type REAL.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type REAL.</exception>
			Single GetReal();

			/// <summary>Gets the value of an array element of type REAL.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type REAL.</exception>
			Single GetReal(UInt16 index);

			/// <summary>Sets the value of a variable of type REAL.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type REAL.</exception>
			void Set(Single value);

			/// <summary>Sets the value of an array element of type REAL.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type REAL.</exception>
			void Set(UInt16 index, Single value);
		//}}}

		//{{{ LREAL
			/// <summary>Gets the value of a variable of type LREAL.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type LREAL.</exception>
			Double GetLongReal();

			/// <summary>Gets the value of an array element of type LREAL.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type LREAL.</exception>
			Double GetLongReal(UInt16 index);

			/// <summary>Sets the value of a variable of type LREAL.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type LREAL.</exception>
			void Set(Double value);

			/// <summary>Sets the value of an array element of type LREAL.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type LREAL.</exception>
			void Set(UInt16 index, Double value);
		//}}}

		//{{{ STRING
			/// <summary>Gets the value of a variable of type STRING.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type STRING.</exception>
			String^ GetString();

			/// <summary>Gets the value of an array element of type STRING.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type STRING.</exception>
			String^ GetString(UInt16 index);

			/// <summary>Sets the value of a variable of type STRING.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type STRING.</exception>
			void Set(String^ value);

			/// <summary>Sets the value of an array element of type STRING.</summary>
			/// <exception cref="AxVariableException">Thrown on handle errors.</exception>
			/// <exception cref="AxVariableTypeException">Thrown when variable is not of type STRING.</exception>
			void Set(UInt16 index, String^ value);
		//}}}

		/// <summary>Gets the description text for an enumeration value.</summary>
		String^ GetEnumText(Int32 enumIndex);
	};
}