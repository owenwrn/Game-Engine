/** \file windowEvent.h */
#pragma once

#include "event.h"
#include <glm/glm.hpp>

namespace Engine
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {
			m_eventType = EventType::WindowClose;
			m_catFlags = EventCategory::Input | EventCategory::Window;
		}
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height) {
			m_eventType = EventType::WindowResize;
			m_catFlags = EventCategory::Input | EventCategory::Window;
			m_width = width;
			m_height = height;
		}
		int32_t getWidth() const { return m_width; }
		int32_t getHeight() const { return m_height; }
		int32_t getCatergoryFlags() const { return m_catFlags; }
		EventType getType() const { return m_eventType; }
		glm::vec2 getSize() const { return glm::vec2(m_width, m_height); }
	protected:
		int32_t m_width;
		int32_t m_height;
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() {
			m_eventType = EventType::WindowFocus;
			m_catFlags = EventCategory::Input | EventCategory::Window;
		}
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent() {
			m_eventType = EventType::WindowLostFocus;
			m_catFlags = EventCategory::Input | EventCategory::Window;
		}
	};

	class WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent(int32_t xpos, int32_t ypos) {
			m_eventType = EventType::WindowResize;
			m_catFlags = EventCategory::Input | EventCategory::Window;
			m_x = xpos;
			m_y = ypos;
		}

		int32_t getX() const { return m_x; }
		int32_t getY() const { return m_y; }
	protected:
		int32_t m_x;
		int32_t m_y;
	};

}