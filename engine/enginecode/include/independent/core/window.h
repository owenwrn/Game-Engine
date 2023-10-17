/** \file window.h */
#pragma once

#include "events/eventHandler.h"

namespace Engine
{
	/** \class Window
	* Abstract window base class. All implemented windows should code to this interface
	*/

	struct WindowProperties
	{
		char* m_title;
		unsigned int m_width;
		unsigned int m_height;
		bool m_isFullScreen;
		bool m_isVsync;

		WindowProperties(char* title = "My Window", unsigned int width = 800, unsigned int height = 600, bool fullscreen = false) : 
			m_title(title),
			m_width(width),
			m_height(height), 
			m_isFullScreen(fullscreen)
		{}
	};

	class WindowBase
	{
	public:
		virtual void init(const WindowProperties& properties) = 0; //!< Initialise the window
		virtual void close() = 0; //!< Close the window
		virtual ~WindowBase() {}; //!< Deconstructor
		virtual void onUpdate(float timestep) = 0; //!< On update function
		virtual void setVsync(bool Vsync) = 0; //!< sets Vsync
		virtual unsigned int getWidth() const = 0; //!< Gets screen width
		virtual unsigned int  getHeight() const = 0; //!< Gets screen height
		virtual void* getNativeWindow() const = 0; //!< Gets native window
		virtual bool isFullCreenMode() const = 0; //<! Check if screen is in fullscreen mode
		virtual bool isVsync() const = 0; //!< Checks if Vysnced

		inline EventHandler& getEventHandler() { return m_handler; }

		static WindowBase* create(const WindowProperties& properties = WindowProperties());
	protected:
		EventHandler m_handler; //!< Event handler


	};

}