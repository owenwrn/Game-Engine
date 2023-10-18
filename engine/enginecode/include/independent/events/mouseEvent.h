/** \file mouseEvent.h */
#pragma once
#include"events.h"

namespace Engine
{
	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(int32_t code) :
			Event(EventType::MoueButtonPressed, EventCategory::MouseButton | EventCategory::Input),
			m_code(code)
		{}
		int32_t getCode() { return m_code; }
	protected:
		int32_t m_code; //!< Lib specific code
	};

	class MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent(int32_t code) :
			Event(EventType::MouseButtonReleased, EventCategory::MouseButton | EventCategory::Input),
			m_code(code)
		{}
		int32_t getCode() { return m_code; }
	protected:
		int32_t m_code; //!< Lib specific code
	};
	
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(int32_t xpos, int32_t ypos) :
			Event(EventType::MouseMoved, EventCategory::Mouse | EventCategory::Input),
			m_x(xpos),
			m_y(ypos)
		{}
		int32_t getX() const { return m_x; }
		int32_t getY() const { return m_y; }
	protected:
		int32_t m_x; //!< x position
		int32_t m_y; //!< y position
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(int32_t xOffset, int32_t yOffset) :
			Event(EventType::MouseScrolled, EventCategory::Mouse | EventCategory::Input),
			m_xOffset(xOffset),
			m_yOffset(yOffset)
		{}

		int32_t getXOffset() const { return m_xOffset; }
		int32_t getYOffset() const { return m_yOffset; }

	protected:
		int32_t m_xOffset; //!< x Offset
		int32_t m_yOffset; //!< y Offset
	};
}