#pragma once
#include "Event.h"

namespace SandTable
{
	class SystemDispatcher
	{
	public:
		SystemDispatcher(Event& eEvent)
			: m_eEvent(eEvent)
		{

		}

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_eEvent.GetEventType() == T::GetStaticEventType())
			{
				func(static_cast<T&>(m_eEvent));
				return true;
			}
			return false;
		}
	private:
		Event& m_eEvent;
	};
}
