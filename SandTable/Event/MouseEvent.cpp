#pragma once
#include"MouseEvent.h"

namespace SandTable
{
	//MouseMoveEvent
	MouseMoveEvent::MouseMoveEvent(float fX, float fY):m_fX(fX),m_fY(fY)
	{
	}

	float MouseMoveEvent::GetX() const
	{
		return m_fX;
	}

	float MouseMoveEvent::GetY() const
	{
		return m_fY;
	}

	EventType MouseMoveEvent::GetStaticEventType()
	{
		return EventType::MouseMove;
	}

	EventType MouseMoveEvent::GetEventType() const
	{
		return GetStaticEventType();
	}

	//MouseScrollEvent
	MouseScrollEvent::MouseScrollEvent(float fX, float fY) :m_fXOffset(fX),m_fYOffset(fY)
	{
	}

	float MouseScrollEvent::GetXOffset() const
	{
		return m_fXOffset;
	}

	float MouseScrollEvent::GetYOffset() const
	{
		return m_fYOffset;
	}

	EventType MouseScrollEvent::GetStaticEventType()
	{
		return EventType::MouseScroll;
	}

	EventType MouseScrollEvent::GetEventType()const
	{
		return GetStaticEventType();
	}
}
