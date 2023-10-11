/** \file windows.h */
#pragma once

#include "event.h"

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
	protected:
		int m_width;
		int m_height;
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
		WindowMovedEvent(int xpos, int ypos) {
			m_eventType = EventType::WindowResize;
			m_catFlags = EventCategory::Input | EventCategory::Window;
			m_x = xpos;
			m_y = ypos;
		}
	protected:
		int m_x;
		int m_y;
	};

}