/* \file inputPoller.h */
#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Engine
{
	/* \class InputPoller
	*   GLFW input poller for getting keyboard/mouse state
	*/
	class InputPoller
	{
	public:
		static bool isKeyPressed(int32_t keyCode); //!< is the key pressed
		static bool isMouseButtonPressed(int32_t mouseButton); //!< is the mouse button pressed
		static glm::vec2 getMousePosition(); //!< current mouse position
		static void setNativeWindow(void* nativeWin);
		inline static float getMouseX() { return getMousePosition().x; }
		inline static float getMouseY() { return getMousePosition().y; }
	private:
		inline static GLFWwindow* s_window = nullptr; //!< Current GLFW window
	};
}