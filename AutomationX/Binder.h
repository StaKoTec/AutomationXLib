#pragma once

namespace AutomationX
{
	public ref class AnyDelegateWrapper
	{
	public:
		System::Delegate^ target;
		array<System::Object^>^ args;

		void Execute()
		{
			target->DynamicInvoke(args);
		}
	};

	public ref class Binder
	{
	public:
		static System::Action^ Bind(System::Delegate^ d, ... array<System::Object^>^ args)
		{
			AnyDelegateWrapper^ w = gcnew AnyDelegateWrapper();
			w->target = d;
			w->args = args;
			return gcnew System::Action(w, &AnyDelegateWrapper::Execute);
		}
	};
}