/* \file indexBuffer.h */
#pragma once

#include <cstdint>

namespace Engine
{
	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t* indices, uint32_t count); //!< Constructor
		~IndexBuffer(); //!< Destructor
		inline uint32_t getRenderID() const { return m_OpenGL_ID; } //!< Get Render Id
		inline uint32_t getCount() const { return m_count; } //!< Get the count

	private:
		uint32_t m_OpenGL_ID; //!< RenderID
		uint32_t m_count; //!< Effective draw count
	};
}