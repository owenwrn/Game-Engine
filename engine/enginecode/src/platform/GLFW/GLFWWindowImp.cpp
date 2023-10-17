/** \file GLFWWindowImp.cpp */

#include "engine_pch.h"
#include "platform/GLFW/GLFWWindowImp.h"

namespace Engine {

#ifdef NG_PLATFORM_WINDOWS
	WindowBase* WindowBase::create(const WindowProperties& properties = WindowProperties()) {

		return new GLFWWindowImp(properties);
	}
#endif

	GLFWWindowImp::GLFWWindowImp(const WindowProperties& properties)
	{
		init(properties);
	}

	void GLFWWindowImp::init(const WindowProperties& properties)
	{
	}

	void GLFWWindowImp::close()
	{
	}

	void GLFWWindowImp::onUpdate(float timestep)
	{
	}

	void GLFWWindowImp::setVsync(bool Vsync)
	{
	}
}