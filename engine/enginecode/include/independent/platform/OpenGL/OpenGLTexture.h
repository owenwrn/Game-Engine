/* \file OpenGLTexture.h*/
#pragma once

#include <cstdint>

namespace Engine
{
	class OpenGLTexture
	{
	public:
		OpenGLTexture(const char* filePath); //!< Constructor which takes a file path
		OpenGLTexture(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data); //!< Constructor which takes width height number of channels and data
		~OpenGLTexture(); //!< Destructor
		void edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char* data); //!< Edits texture channels
		inline uint32_t getID() { return m_OpenGL_ID; } //!< Returns OpenGL ID
		inline uint32_t getWidth() { return m_width; } //!< Returns Width
		inline uint32_t getHeight() { return m_height; } //!< Returns Height
		inline uint32_t getWidthf() const { return static_cast<float>(m_width); } //!<  Returns Width as a float
		inline uint32_t getHeightf() const { return static_cast<float>(m_height); } //!<  Returns Height as a float
		inline uint32_t getChannels() { return m_channels; } //!< Returns channels
		void bindToSlot(uint32_t slot); //!< Binds texture to a slot
	private:
		uint32_t m_OpenGL_ID; //!< OpenGL ID
		uint32_t m_width; //!< width
		uint32_t m_height; //!< Height
		uint32_t m_channels; //!< Channels

		void init(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data); //!< Initialise texture

	};
}