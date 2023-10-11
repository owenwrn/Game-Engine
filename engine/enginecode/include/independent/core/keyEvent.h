/** \file keyEvents.h*/
#pragma once

#include "event.h"

namespace Engine
{
	class KeyEvent : public Event
	{
	public:
		KeyEvent(int32_t code, int32_t count) :
			Event(EventType::KeyPressed, EventCategory::Keyboard | EventCategory::Input),
			m_keyCode (code),
			m_repeatCount(count)
		{}
	protected:
		int32_t m_keyCode; //!< Lib specific code
		int32_t m_repeatCount; //!< Repeat count for key
	};
}