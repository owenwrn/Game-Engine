/** \file application.cpp
*/

#include "engine_pch.h"
#include <glad/glad.h>
#include "core/application.h"

#ifdef NG_PLATFORM_WINDOWS
#include "platform/windows/winTimer.h"
#endif

#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWSystem.h"
#endif

namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		// Start systems

		// Start log
		m_logSystem.reset(new Log);
		m_logSystem->start();

		//Start the windows System
#ifdef NG_PLATFORM_WINDOWS
		m_windowsSystem.reset(new GLFWSystem);
#endif
		m_windowsSystem->start();


		// reset timer
#ifdef NG_PLATFORM_WINDOWS
		m_timer.reset(new WinTimer);
#else
		m_timer.reset(new ChronoTimer);
#endif
		m_timer->start();

		WindowProperties props("My Game Engine", 1024, 800);
		m_window.reset(WindowBase::create(props));

		// Set up callbacks
		m_window->getEventHandler().setOnWinClose(std::bind(&Application::onClose, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWinResize(std::bind(&Application::onResize, this, std::placeholders::_1));
		m_window->getEventHandler().setOnKeyPressed(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));
		m_window->getEventHandler().setOnKeyReleased(std::bind(&Application::onKeyReleased, this, std::placeholders::_1));

	
		
	}

	void Application::onClose(WindowCloseEvent& e)
	{
		Log::info("Shutting down");
		m_running = false;
	}

	bool Application::onResize(WindowResizeEvent& e)
	{
		e.handle(true);
		Log::info("Window Resize event: ({0}, {1})", e.getWidth(), e.getHeight());
		return e.handled();;
	}

	bool Application::onKeyPressed(KeyPressedEvent& e)
	{
		e.handle(true);
		Log::info("Key pressed event: key: {0}, repeat: {1}", e.getKeyCode(), e.getRepeatCount());
		return e.handled();;
	}

	bool Application::onKeyReleased(KeyReleasedEvent& e)
	{
		e.handle(true);
		Log::info("Key released event: key: {0}", e.getKeyCode());
		return e.handled();;
	}



	Application::~Application()
	{

		// Stop systems

		// Stop log
		m_logSystem->stop();
		// Stop windows system
		m_windowsSystem->stop();
	}


	void Application::run()
	{
		float timestep = 0.1f;

		glEnable(GL_DEPTH);
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		while (m_running)
		{
			timestep = m_timer->getTimeElapsed();
			m_timer->reset();
			//Log::trace("FPS {0}", 1.0f / timestep);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_window->onUpdate(timestep);
		
		};
	}

}
