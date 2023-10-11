/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"

#ifdef NG_PLATFORM_WINDOWS
#include "platform/windows/winTimer.h"
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

		// reset timer
#ifdef NG_PLATFORM_WINDOWS
		m_timer.reset(new WinTimer);
#else
		m_timer.reset(new ChronoTimer);
#endif
		m_timer->start();

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
	}


	void Application::run()
	{
		float timestep = 0.1f;
		float acc = 0;
		while (m_running)
		{
			timestep = m_timer->getTimeElapsed();
			acc += timestep;
			m_timer->reset();
			Log::trace("FPS {0}", 1.0f / timestep);
			
			if (acc > 3.f)
			{
				auto& callback = m_eventHandler.getOnWinClose();
				WindowCloseEvent wce;

				callback(wce);
			}

			auto& callbackFocus = m_eventHandler.getOnWinFocus();
			WindowFocusEvent wfe;

			callbackFocus(wfe);

			auto& callbackResize = m_eventHandler.getOnWinResize();
			WindowResizeEvent wre(800, 600);

			callbackResize(wre);
		};
	}

}
