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

TEST(Events, ResizeConstructor) {
	Engine::WindowResizeEvent e(800, 600);

	int32_t width1 = e.getWidth();
	int32_t height1 = e.getHeight();

	auto size = e.getSize();
	int32_t width2 = size.x;
	int32_t height2 = size.y;
	int32_t cat = e.getCatergoryFlags();
	Engine::EventType type = e.getType();
	

	EXPECT_EQ(width1, 800);
	EXPECT_EQ(width2, 800);
	EXPECT_EQ(height1, 600);
	EXPECT_EQ(height2, 600);
	EXPECT_EQ(cat, Engine::EventCategory::Input | Engine::EventCategory::Window);
	EXPECT_EQ(type, Engine::EventType::WindowResize);
	
}