/* \file indexBuffer.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "platform/OpenGL/indexBuffer.h"

namespace Engine
{
	IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count) : m_count(count)
	{
		glCreateBuffers(1, &m_OpenGL_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_OpenGL_ID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uint32_t) * count, indices, GL_STATIC_DRAW);
	}
	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_OpenGL_ID);
	}
}