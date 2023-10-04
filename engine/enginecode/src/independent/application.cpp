/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"

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

	}

	Application::~Application()
	{

		// Stop systems

		// Stop log
		m_logSystem->stop();
	}


	void Application::run()
	{
		while (m_running)
		{
			Log::file("Hello world! {0} {1}", 42, "my name is");

		};
	}

}
