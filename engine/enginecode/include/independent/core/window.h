/** \file window.h */
#pragma once

#include "events/eventHandler.h"
#include "core/graphicsContext.h"

namespace Engine
{
	/** \class Window
	* Abstract window base class. All implemented windows should code to this interface
	*/

	struct WindowProperties
	{
		char* title;
		uint32_t width;
		uint32_t height;
		bool isFullScreen;
		bool isVsync;

		WindowProperties(char* title = "My Window", uint32_t width = 800, uint32_t height = 600, bool fullscreen = false) :
			title(title),
			width(width),
			height(height), 
			isFullScreen(fullscreen)
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
		std::shared_ptr<GraphicsContext> m_graphicsContext;

	};

}