#pragma once

#include "Event.h"

namespace SandTable
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int iWindowWidth, int iWindowHeight);
		int GetWindowWidth()const;
		int GetWindowHeight()const;
		static EventType GetStaticEventType();
		EventType GetEventType() const;

	private:
		int m_iWindowWidth;
		int m_iWindowHeight;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;
		static EventType GetStaticEventType();
		EventType GetEventType() const;
	};
}