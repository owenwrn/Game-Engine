/** \file eventHandler.h */
#pragma once

#include <functional>
#include "events.h"

namespace Engine
{
	class EventHandler 
	{
	public:
		void setOnWinClose(const std::function<void(WindowCloseEvent& e)>& func) { m_onWinClose = func; }
		std::function<void(WindowCloseEvent& e)>& getOnWinClose() { return m_onWinClose; }
	private:
		std::function<void(WindowCloseEvent& e)> m_onWinClose = [](const WindowCloseEvent& e) {};
	};
}