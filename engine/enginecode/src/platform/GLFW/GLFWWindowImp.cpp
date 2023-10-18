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