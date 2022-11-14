#pragma once
#include "KeyEvent.h"

namespace SandTable
{
	//KeyPress
	KeyPressEvent::KeyPressEvent(int iKeyCode):m_iKeyCode(iKeyCode)
	{

	}

	int KeyPressEvent::GetKeyCode() const
	{
		return m_iKeyCode;
	}

	EventType KeyPressEvent::GetStaticEventType()
	{
		return EventType::KeyPress;
	}

	EventType KeyPressEvent::GetEventType() const
	{
		return GetStaticEventType();
	}
}
