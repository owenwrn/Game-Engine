/** \file event */
#pragma once

#include <inttypes.h>

namespace Engine {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyRelease, KeyTyped,
		MoueButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		Window = 1 << 0,
		Input = 1 << 1,
		Keyboard = 1 << 2,
		Mouse = 1 << 3,
		MouseButton = 1 << 4,
	};

	/** \class event
		* event base class
		*/
	class Event
	{
	public:
		Event() {}; //!< Default
		Event(EventType type, int32_t catFlags) :
			m_eventType(type), m_catFlags(catFlags)
		{}
		inline bool handled() const { return m_handled; }
		inline void handle(bool isHandled) { m_handled = isHandled; }
	protected:
		EventType m_eventType = EventType::None; //!< Type of this event
		int32_t m_catFlags = EventCategory::None; //!< Category flags of this event
		bool m_handled = false; //!< Has the event been handled
	};

}
