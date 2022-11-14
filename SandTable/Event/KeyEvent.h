#pragma once
#include <GLFW/glfw3.h>
#include "Event.h"

namespace SandTable
{
	class KeyPressEvent :public Event
	{
	public:
		KeyPressEvent(int iKeyCode);
		int GetKeyCode() const;
		static EventType GetStaticEventType();
		EventType GetEventType() const override;
	private:
		int m_iKeyCode;
	};
}
