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

		template<typename EventType, typename CallBack>
		bool Dispatch(const CallBack& func)
		{
			if (m_eEvent.GetEventType() == EventType::GetStaticEventType())
			{
				func(static_cast<EventType&>(m_eEvent));
				return true;
			}
			return false;
		}
	private:
		Event& m_eEvent;
	};
}
