#include "engine_pch.h"
#include "platform/GLFW/inputPoller.h"

namespace Engine
{
	bool InputPoller::isKeyPressed(int32_t keyCode)
	{
		if (s_window)
		{
			auto keyState = glfwGetKey(s_window, keyCode);
			return keyState == GLFW_PRESS || keyState == GLFW_REPEAT;
		}
		return false;
			
	}
	bool InputPoller::isMouseButtonPressed(int32_t mouseButton)
	{
		if (s_window)
		{
			return glfwGetMouseButton(s_window, mouseButton) == GLFW_PRESS;
		
		}
		return false;
	}
	glm::vec2 InputPoller::getMousePosition()
	{
		if (s_window)
		{
			double x, y;
			glfwGetCursorPos(s_window, &x, &y);
			return glm::vec2(static_cast<float>(x), static_cast<float>(y));

		}
		return glm::vec2(-1, -1);
	}
	void InputPoller::setNativeWindow(void* nativeWin)
	{
		s_window = reinterpret_cast<GLFWwindow*>(nativeWin);
	}
}