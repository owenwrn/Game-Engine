#pragma once
#include <gtest/gtest.h>

#include "events/eventHandler.h"
#include "events/keyEvent.h"

namespace EventTests
{
	std::shared_ptr<Engine::EventHandler> handler;




	void init()
	{
		handler.reset(new Engine::EventHandler);
		//window events
		handler->setOnWinClose([](Engine::WindowCloseEvent& e) {e.handle(true); });
		handler->setOnWinFocus([](Engine::WindowFocusEvent& e) {e.handle(true); });
		handler->setOnWinLostFocus([](Engine::WindowLostFocusEvent& e) {e.handle(true); });
		handler->setOnWinMoved([](Engine::WindowMovedEvent& e) {e.handle(true); });
		handler->setOnWinResize([](Engine::WindowResizeEvent& e) {e.handle(true); });
		//key events
		handler->setOnKeyPressed([](Engine::KeyPressedEvent& e) {e.handle(true); });
		handler->setOnKeyReleased([](Engine::KeyReleasedEvent& e) {e.handle(true); });
		handler->setOnKeyType([](Engine::KeyTypeEvent& e) {e.handle(true); });
		//Mouse events
		handler->setOnMouseButtonPressed([](Engine::MouseButtonPressedEvent& e) {e.handle(true); });
		handler->setOnMouseButtonReleased([](Engine::MouseButtonReleasedEvent& e) {e.handle(true); });
		handler->setOnMouseMoved([](Engine::MouseMovedEvent& e) {e.handle(true); });
		handler->setOnMouseScrolled([](Engine::MouseScrolledEvent& e) {e.handle(true); });
	}


}