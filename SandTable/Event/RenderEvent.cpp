#pragma once
#include "RenderEvent.h"

namespace SandTable
{
	//WindowResizeEvent
	WindowResizeEvent::WindowResizeEvent(int iWindowWidth, int iWindowHeight):
		m_iWindowWidth(iWindowWidth), m_iWindowHeight(iWindowHeight)
	{

	}

	int WindowResizeEvent::GetWindowWidth()const
	{
		return m_iWindowWidth;
	}

	int WindowResizeEvent::GetWindowHeight() const 
	{ 
		return m_iWindowHeight;
	}

	EventType WindowResizeEvent::GetStaticEventType()
	{
		return EventType::WindowResize;
	}

	EventType WindowResizeEvent::GetEventType() const
	{
		return GetStaticEventType();
	}

	//WindowResizeEvent
	EventType WindowCloseEvent::GetStaticEventType()
	{
		return EventType::WindowClose;
	}

	EventType WindowCloseEvent::GetEventType() const
	{
		return GetStaticEventType();
	}
}