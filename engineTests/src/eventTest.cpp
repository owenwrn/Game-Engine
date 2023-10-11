#include "eventTest.h"

TEST(EventTest, HandledCorrectly) {

	if (!EventTests::handler) EventTests::init();

	Engine::WindowCloseEvent wce;

	bool before = wce.handled();

	auto& callback = EventTests::handler->getOnWinClose();

	callback(wce);

	bool after = wce.handled();

	EXPECT_FALSE(before);
	EXPECT_TRUE(after);
}