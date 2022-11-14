#pragma once
#include "Event.h"

namespace SandTable
{
	class SystemDispatcher
	{
	public:
		SystemDispatcher(std::shared_ptr<Event> spEvent)
			: m_spEvent(spEvent)
		{

		}

		template<typename EventType, typename CallBack>
		bool Dispatch(const CallBack& callBack)
		{
			if (m_spEvent->GetEventType == EventType::GetStaticType())
			{
				return callBack(static_cast<T&>(m_Event));
			}
			return false;
		}
	private:
		std::shared_ptr<Event> m_spEvent;
	};
}
