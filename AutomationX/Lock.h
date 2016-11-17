#pragma once

using namespace System::Threading;

namespace AutomationX
{
	ref class Lock
	{
	private:
		Object^ m_pObject;

	public:
		explicit Lock(Object^ pObject) : m_pObject(pObject)
		{
			Monitor::Enter(m_pObject);
		}

		~Lock()
		{
			Monitor::Exit(m_pObject);
		}
	};

	ref class ResetEventLock
	{
	private:
		ManualResetEvent^ m_pResetEvent;

	public:
		explicit ResetEventLock(ManualResetEvent^ pResetEvent) : m_pResetEvent(pResetEvent)
		{
		}

		~ResetEventLock()
		{
			if (m_pResetEvent) m_pResetEvent->Set();
		}
	};
}