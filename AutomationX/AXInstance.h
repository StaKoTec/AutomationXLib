#pragma once

using namespace System;
using namespace System::Collections::Generic;

#include "ManagedTypeConverter.h"
#include "AxVariable.h"

namespace AutomationX
{
	public ref class AxInstance : IDisposable
	{
	private:
		Ax^ _ax = nullptr;
		ManagedTypeConverter _converter;
		AxVariable::ValueChangedEventHandler^ _variableValueChangedDelegate = nullptr;
		AxVariable::ArrayValueChangedEventHandler^ _arrayValueChangedDelegate = nullptr;
		ManualResetEvent^ _initResetEvent = gcnew ManualResetEvent(false);
		bool _initComplete = false;
		Object^ _spsIdChangedMutex = gcnew Object();
		UInt32 _spsIdChangedCallbackId = 0;

		//{{{ Properties
			bool _reloadRequired = false;
			bool _cleanUp = false;
			String^ _name = "";
			String^ _className = "";
			String^ _remark = "";
			AxInstance^ _parent = nullptr;
			Object^ _variableListMutex = gcnew Object();
			List<AxVariable^>^ _variableList = gcnew List<AxVariable^>();
			Dictionary<String^, AxVariable^>^ _variables = gcnew Dictionary<String^, AxVariable^>();
			Object^ _subinstanceListMutex = gcnew Object();
			List<AxInstance^>^ _subinstanceList = gcnew List<AxInstance^>();
			Dictionary<String^, AxInstance^>^ _subinstances = gcnew Dictionary<String^, AxInstance^>();
		//}}}

		//{{{ Queueable methods
			delegate void NoParameterDelegate();
			delegate bool NoParameterReturnBoolDelegate();
			delegate void ResetEventParameterDelegate(ManualResetEvent^ resetEvent);

			void InvokeGetClassName();
			void GetClassName();

			void InvokeGetRemark();
			void GetRemark();

			void InvokeGetVariables();

			ref class GetSubinstancesData
			{
			public:
				UInt32 InstanceCount = 0;
				AxSubInstanceList_StructPt PInstanceList = nullptr;

				void CleanUp()
				{
					if (PInstanceList)
					{
						pin_ptr<AxSubInstanceList_StructPt> ppInstanceList = &PInstanceList;
						AxFreeSubInstanceList(ppInstanceList);
						PInstanceList = nullptr;
					}
				}

				virtual ~GetSubinstancesData()
				{
					this->!GetSubinstancesData();
				}

				!GetSubinstancesData()
				{
					CleanUp();
				}
			};
			delegate void GetSubinstancesDelegate(GetSubinstancesData^ data);
			void InvokeGetSubinstances(GetSubinstancesData^ data);
			GetSubinstancesData^ GetVariablesAndSubinstances();
			delegate void InitFinishedDelegate(ManualResetEvent^ resetEvent, GetSubinstancesData^ data, bool wait);
			void InvokeInitFinished(ManualResetEvent^ resetEvent, GetSubinstancesData^ data, bool wait);
			void InitFinished(GetSubinstancesData^ data, bool wait);
		//}}}

		void LoadSubinstances(GetSubinstancesData^ data);

		/// <summary>Gets a raw aX handle. Only call this method if within the main loop!!!</summary>
		void* GetRawHandle();

		void OnValueChanged(AxVariable^ sender, AxVariableValue^ value, DateTime timestamp);

		void OnArrayValueChanged(AxVariable^ sender, UInt16 index, AxVariableValue^ value, DateTime timestamp);

		bool SpsIdChanged();
	internal:
		property Ax^ AxObject { Ax^ get() { return _ax; }; }
		bool ReloadStaticProperties(bool wait);
		void SetReloadRequired();
		void SetCleanUp();
	public:
		/// <summary>Fired when the value of one the instance's a variable is changed in aX. Only raised, after "VariableEvents" has been enabled or after manually calling "Refresh".</summary>
		event AxVariable::ValueChangedEventHandler^ VariableValueChanged;

		/// <summary>Fired when the value of an array element is changed in aX. Only raised, after "VariableEvents" has been enabled or after manually calling "Refresh".</summary>
		event AxVariable::ArrayValueChangedEventHandler^ ArrayValueChanged;

		/// <summary>Returns true if the instance needs to be recreated.</summary>
		property bool ReloadRequired { bool get() { return _reloadRequired; } }

		/// <summary>Returns true if the instance does not exist anymore.</summary>
		property bool CleanUp { bool get() { return _cleanUp; }; }
		property String^ Name { String^ get() { return _name; }; }
		property String^ Path { String^ get() { if (_parent) return _parent->Path + "." + _name; else return _name; } }
		property String^ ClassName { String^ get() { return _className; }; }
		property String^ Remark { String^ get() { return _remark; }; }

		/// <summary>Returns the parent instance.</summary>
		property AxInstance^ Parent { AxInstance^ get() { return _parent; } }

		/// <summary>Returns a collection of all variables.</summary>
		property array<AxVariable^>^ Variables { array<AxVariable^>^ get(); }

		/// <summary>Returns a collection of all subinstances.</summary>
		property array<AxInstance^>^ Subinstances { array<AxInstance^>^ get(); }

		/// <summary>Returns the aX variable of the specified name.</summary>
		/// <param name='variableName'>The name of the variable.</param>
		/// <return>Returns an aX variable object or null, when the variable was not found.</return>
		property AxVariable^ default[String^] { AxVariable^ get(String^ variableName); }

		/// <summary>Constructor</summary>
		/// <param name='ax'>The aX object.</param>
		/// <param name='name'>Name of this aX instance.</param>
		AxInstance(Ax^ ax, String^ name);

		/// <summary>Constructor</summary>
		/// <param name='ax'>The aX object.</param>
		/// <param name='name'>Name of this aX subinstance.</param>
		AxInstance(Ax^ ax, AxInstance^ parent, String^ name);

		/// <summary>Constructor</summary>
		/// <param name='ax'>The aX object.</param>
		/// <param name='name'>Name of this aX instance.</param>
		/// <param name='waitForInitCompleted'>Default is "true". When set to "false" the constructor returns immediately after all init methods are queued. Call "WaitForInitCompleted()" on the last constructed instance before using the object.</param>
		AxInstance(Ax^ ax, String^ name, bool waitForInitCompleted);

		/// <summary>Constructor</summary>
		/// <param name='ax'>The aX object.</param>
		/// <param name='name'>Name of this aX subinstance.</param>
		/// <param name='waitForInitCompleted'>Default is "true". When set to "false" the constructor returns immediately after all init methods are queued. Call "WaitForInitCompleted()" on the last constructed instance before using the object.</param>
		AxInstance(Ax^ ax, AxInstance^ parent, String^ name, bool waitForInitCompleted);

		virtual ~AxInstance();
		!AxInstance();

		/// <summary>Returns the aX variable of the specified name.</summary>
		/// <param name='variableName'>The name of the variable.</param>
		/// <return>Returns an aX variable object or null, when the variable was not found.</return>
		AxVariable^ Get(String^ variableName);

		/// <summary>Returns the subinstance of the specified name.</summary>
		/// <param name='instanceName'>The name of the subinstance.</param>
		/// <return>Returns an instance object or null, when the subinstance was not found.</return>
		AxInstance^ GetSubinstance(String^ instanceName);

		/// <summary>Checks if a variable exists.</summary>
		/// <returns>True when the variable name was found, otherwise false.</returns>
		bool VariableExists(String^ variableName);

		/// <summary>Checks if a subinstance exists.</summary>
		/// <returns>True when the subinstance name was found, otherwise false.</returns>
		bool SubinstanceExists(String^ subinstanceName);

		/// <summary>Waits for init to complete if "waitForInitComplete" is set to "false" in constructor. This method only needs to be called on the last initialized instance of the thread.</summary>
		void WaitForInitCompleted();
	};
}

