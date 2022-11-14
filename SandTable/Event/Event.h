#pragma once
#include <functional>
#include <memory>

namespace SandTable
{
#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)
	enum EventType
	{
		WindowClose, WindowResize, Update, Render,
		KeyPress,
		MouseMove, MouseScroll
	};

	class Event
	{
	public:
		virtual ~Event() {};
		virtual EventType GetEventType() const = 0;
	};
}

