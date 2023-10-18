/** \file GLFW_OpenGL_GC.H */
#pragma once

#include "core/graphicsContext.h"

namespace Engine
{
	class GLFW_OpenGL_GC : public GraphicsContext
	{
	public:
		GLFW_OpenGL_GC(GLFWwindow* win) :m_window(win) {}
		virtual void init() override; //!< Init the graphics context for the given windowing API
		virtual void swapBuffers() override; //!< Swap the front and back buffer (double buffering)

	private:
		GLFWwindow* m_window; //!< Poiner o GLFW Window
	};

}