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
}