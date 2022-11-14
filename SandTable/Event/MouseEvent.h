#pragma once

#include "Event.h"

namespace SandTable
{
	class MouseMoveEvent :public Event
	{
	public:
		MouseMoveEvent(float fX, float fY);
		float GetX()const;
		float GetY()const;
		static EventType GetStaticEventType();
		EventType GetEventType()const override;
	private:
		float m_fX;
		float m_fY;
	};

	class MouseScrollEvent :public Event
	{
	public:
		MouseScrollEvent(float fXOffset, float fYOffset);
		float GetXOffset()const;
		float GetYOffset()const;
		static EventType GetStaticEventType();
		EventType GetEventType() const override;
	private:
		float m_fXOffset;
		float m_fYOffset;
	};
}
