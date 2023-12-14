#include "eventTest.h"

TEST(EventTest, HandledCorrectly) {

	if (!EventTests::handler) EventTests::init();

	Engine::WindowCloseEvent wce;
	Engine::WindowFocusEvent wfe;
	Engine::WindowLostFocusEvent wlfe;
	Engine::WindowMovedEvent wme(1.f, 1.f);
	Engine::WindowResizeEvent wre(1.f, 1.f);

	bool before = wce.handled();

	auto& callback1 = EventTests::handler->getOnWinClose();

	callback1(wce);

	bool after = wce.handled();

	EXPECT_FALSE(before);
	EXPECT_TRUE(after);

	before = wfe.handled();

	auto& callback2 = EventTests::handler->getOnWinFocus();

	callback2(wfe);

	after = wfe.handled();

	EXPECT_FALSE(before);
	EXPECT_TRUE(after);

	before = wlfe.handled();

	auto& callback3 = EventTests::handler->getOnWinLostFocus();

	callback3(wlfe);

	after = wlfe.handled();

	EXPECT_FALSE(before);
	EXPECT_TRUE(after);

	before = wme.handled();

	auto& callback4 = EventTests::handler->getOnWinMoved();

	callback4(wme);

	after = wme.handled();

	EXPECT_FALSE(before);
	EXPECT_TRUE(after);

	before = wre.handled();

	auto& callback5 = EventTests::handler->getOnWinResize();

	callback5(wre);

	after = wre.handled();

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

