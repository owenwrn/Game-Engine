/** \file application.h
*/
#pragma once

#include "systems/log.h"
#include "timer.h"
#include "events/eventHandler.h"
#include "events/events.h"
#include "window.h"


namespace Engine {

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	protected:
		Application(); //!< Constructor

		std::shared_ptr<Log> m_logSystem; //!< Log system
		std::shared_ptr<System> m_windowsSystem; //!< Windows System
		std::shared_ptr<WindowBase> m_window; //!< Window

	std::shared_ptr<Timer> m_timer; //!< Timer

		void onClose(WindowCloseEvent & e); //!< Run when the window is closed
		bool onResize(WindowResizeEvent& e); //!< Run when the window is resized
		bool onMove(WindowMovedEvent& e); //!< Run when the window is moved
		bool onKeyPressed(KeyPressedEvent& e); //!< Run when the key is pressed
		bool onKeyReleased(KeyReleasedEvent& e); //!< Run when the key is released
		bool onMouseButtonPressed(MouseButtonPressedEvent& e); //!< Run when the mouse button is Pressed
		bool onMouseButtonReleased(MouseButtonReleasedEvent& e); //!< Run when the mouse button is released
		bool onMouseMove(MouseMovedEvent& e); //!< Run when the mouse is moved

	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?

		EventHandler m_eventHandler;

	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}