/** \file vertexBuffer.H */
#pragma once

#include "rendering/bufferLayout.h"


namespace Engine
{
	class VertexBuffer
	{
	public:
		VertexBuffer(void* vertices, uint32_t size, BufferLayout layout); //!< Default Constructor
		~VertexBuffer(); //!< Destructor
		void edit(void* vertices, uint32_t size, uint32_t offset);
		inline uint32_t getRenderID() const { return m_OpenGL_ID; }
		inline const BufferLayout getLayout() const { return m_layout; }


	private:
		uint32_t m_OpenGL_ID; //!< RenderID
		BufferLayout m_layout;
	};

}