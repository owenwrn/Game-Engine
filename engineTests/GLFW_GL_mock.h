#pragma once

#include "include/independent/platform/GLFW/GLFWSystem.h"
#include "include/independent/platform/GLFW/GLFWWindowImp.h"

class GLFW_GL_mock
{
public:
	GLFW_GL_mock();
	~GLFW_GL_mock();
	std::shared_ptr<Engine::System> glfwSystem;
	std::shared_ptr<Engine::WindowBase> glfwWindow;
};

