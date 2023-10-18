/** \file application.cpp
*/

#include "engine_pch.h"
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
		m_eventHandler.setOnWinClose([this](WindowCloseEvent& e) {this->onClose(e); });
		m_eventHandler.setOnWinResize([this](WindowResizeEvent& e) { Log::info("Window Resize ({}, {})",e.getWidth(), e.getHeight()); });
		m_eventHandler.setOnWinFocus([this](WindowFocusEvent& e) { Log::info("Window Focus"); });
	}

	void Application::onClose(const WindowCloseEvent& e)
	{
		Log::info("Shutting down");
		m_running = false;
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
		while (m_running)
		{
			timestep = m_timer->getTimeElapsed();
			m_timer->reset();
			Log::trace("FPS {0}", 1.0f / timestep);
		
		};
	}

}
