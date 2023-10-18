/** \file keyEvents.h*/
#pragma once

#include "event.h"

namespace Engine
{
	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(int32_t code, int32_t count) :
			Event(EventType::KeyPressed, EventCategory::Keyboard | EventCategory::Input),
			m_keyCode (code),
			m_repeatCount(count)
		{}
		int32_t getKeyCode() { return m_keyCode; }
		int32_t getRepeatCount() { return m_repeatCount; }
	protected:
		int32_t m_keyCode; //!< Lib specific code
		int32_t m_repeatCount; //!< Repeat count for key
	};

	class KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(int32_t code) :
			Event(EventType::KeyPressed, EventCategory::Keyboard | EventCategory::Input),
			m_keyCode(code)
			{}
		int32_t getKeyCode() { return m_keyCode; }
	protected:
		int32_t m_keyCode; //!< Lib specific code
	};

	class KeyTypeEvent : public Event
	{
	public:
		KeyTypeEvent(int32_t code) :
			Event(EventType::KeyPressed, EventCategory::Keyboard | EventCategory::Input),
			m_keyCode(code)
		{}
	protected:
		int32_t m_keyCode; //!< Lib specific code
	};
}