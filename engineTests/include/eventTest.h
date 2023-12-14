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

		handler->setOnWinClose([](Engine::WindowCloseEvent& e) {e.handle(true); });
		handler->setOnWinFocus([](Engine::WindowFocusEvent& e) {e.handle(true); });
		handler->setOnWinLostFocus([](Engine::WindowLostFocusEvent& e) {e.handle(true); });
		handler->setOnWinMoved([](Engine::WindowMovedEvent& e) {e.handle(true); });
		handler->setOnWinResize([](Engine::WindowResizeEvent& e) {e.handle(true); });


	}


}