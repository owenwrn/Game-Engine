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
		void setOnWinResize(const std::function<void(WindowResizeEvent& e)>& func) { m_onWinResize = func; }
		void setOnWinFocus(const std::function<void(WindowFocusEvent& e)>& func) { m_onWinFocus = func; }
		void setOnWinLostFocus(const std::function<void(WindowLostFocusEvent& e)>& func) { m_onWinLostFocus = func; }
		void setOnWinMoved(const std::function<void(WindowMovedEvent& e)>& func) { m_onWinMoved = func; }

		void setOnKeyPressed(const std::function<void(KeyPressedEvent& e)>& func) { m_onKeyPressed = func; }
		void setOnKeyReleased(const std::function<void(KeyReleasedEvent& e)>& func) { m_onKeyReleased = func; }
		void setOnKeyType(const std::function<void(KeyTypeEvent& e)>& func) { m_onKeyType = func; }

		std::function<void(WindowCloseEvent& e)>& getOnWinClose() { return m_onWinClose; }
		std::function<void(WindowResizeEvent& e)>& getOnWinResize() { return m_onWinResize; }
		std::function<void(WindowFocusEvent& e)>& getOnWinFocus() { return m_onWinFocus; }
		std::function<void(WindowLostFocusEvent& e)>& getOnWinLostFocus() { return m_onWinLostFocus; }
		std::function<void(WindowMovedEvent& e)>& getOnWinMoved() { return m_onWinMoved; }

		std::function<void(KeyPressedEvent& e)>& getOnKeyPressed() { return m_onKeyPressed; }
		std::function<void(KeyReleasedEvent& e)>& getOnKeyReleased() { return m_onKeyReleased; }
		std::function<void(KeyTypeEvent& e)>& getOnKeyType() { return m_onKeyType; }
	private:
		std::function<void(WindowCloseEvent& e)> m_onWinClose = [](const WindowCloseEvent& e) {};
		std::function<void(WindowResizeEvent& e)> m_onWinResize = [](const WindowResizeEvent& e) {};
		std::function<void(WindowFocusEvent& e)> m_onWinFocus = [](const WindowFocusEvent& e) {};
		std::function<void(WindowLostFocusEvent& e)> m_onWinLostFocus = [](const WindowLostFocusEvent& e) {};
		std::function<void(WindowMovedEvent& e)> m_onWinMoved = [](const WindowMovedEvent& e) {};

		std::function<void(KeyPressedEvent& e)> m_onKeyPressed = [](const KeyPressedEvent& e) {};
		std::function<void(KeyReleasedEvent& e)> m_onKeyReleased = [](const KeyReleasedEvent& e) {};
		std::function<void(KeyTypeEvent& e)> m_onKeyType = [](const KeyTypeEvent& e) {};

	};
}