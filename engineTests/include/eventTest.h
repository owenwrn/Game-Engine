#pragma once
#include <gtest/gtest.h>

#include "core/eventHandler.h"
#include "core/keyEvent.h"

namespace EventTests
{
	std::shared_ptr<Engine::EventHandler> handler;




	void init()
	{
		handler.reset(new Engine::EventHandler);

		handler->setOnWinClose([](Engine::WindowCloseEvent& e) {e.handle(true); });
	}


}