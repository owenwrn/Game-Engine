/** \file GLFWWindowImp.cpp */

#include "engine_pch.h"
#include "platform/GLFW/GLFWWindowImp.h"
#include "systems/log.h"

namespace Engine {

#ifdef NG_PLATFORM_WINDOWS
	WindowBase* WindowBase::create(const WindowProperties& properties) {

		return new GLFWWindowImp(properties);
	}
#endif

	GLFWWindowImp::GLFWWindowImp(const WindowProperties& properties)
	{
		init(properties);
	}

	void GLFWWindowImp::init(const WindowProperties& properties)
	{
		m_props = properties;

		m_aspectRatio = static_cast<float>(m_props.width) / static_cast<float>(m_props.height);

		if (m_props.isFullScreen)
		{
			Log::error("Fullscreen not implemented");
		}
		else
		{
			m_native = glfwCreateWindow(m_props.width, m_props.height, m_props.title, nullptr, nullptr);
		}

		glfwSetWindowUserPointer(m_native, static_cast<void*>(&m_handler));

		glfwSetWindowCloseCallback(m_native,
			[](GLFWwindow* window)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				auto& onClose = handler->getOnWinClose();

				WindowCloseEvent e;
				onClose(e);
			}
			);
		glfwSetWindowSizeCallback(m_native,
			[](GLFWwindow* window, int newWidth, int newHeight)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				auto& onResize = handler->getOnWinResize();

				WindowResizeEvent e(newWidth, newHeight);
				onResize(e);
			}
			);

		glfwSetKeyCallback(m_native,
			[](GLFWwindow* window, int keyCode, int scancode, int action, int mod)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				
				if (action == GLFW_PRESS)
				{
					auto& onKeyPress = handler->getOnKeyPressed();

					KeyPressedEvent e(keyCode, 0);
					onKeyPress(e);
				}
				else if (action == GLFW_REPEAT)
				{
					auto& onKeyPress = handler->getOnKeyPressed();

					KeyPressedEvent e(keyCode, 1);
					onKeyPress(e);
				}
				else if (action == GLFW_RELEASE)
				{
					auto& onKeyRelease = handler->getOnKeyReleased();

					KeyReleasedEvent e(keyCode);
					onKeyRelease(e);
				}
				
			}
		);
	}

	void GLFWWindowImp::close()
	{
		glfwDestroyWindow(m_native);
	}

	void GLFWWindowImp::onUpdate(float timestep)
	{
		glfwPollEvents();
	}

	void GLFWWindowImp::setVsync(bool Vsync)
	{
		m_props.isVsync = Vsync;
		if (m_props.isVsync)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
		
	}
}