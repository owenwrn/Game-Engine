/* \file indexBuffer.h */
#pragma once

#include <cstdint>

namespace Engine
{
	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t* indices, uint32_t count);
		~IndexBuffer();
		inline uint32_t getRenderID() const { return m_OpenGL_ID; }
		inline uint32_t getCount() const { return m_count; }

	private:
		uint32_t m_OpenGL_ID; //!< RenderID
		uint32_t m_count; //!< Effective draw count
	};
}