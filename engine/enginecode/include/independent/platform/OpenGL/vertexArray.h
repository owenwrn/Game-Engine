/* \file vertexArray.h*/
#pragma once

#include <vector>
#include <memory>
#include "vertexBuffer.h"
#include "indexBuffer.h"

namespace Engine
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
		inline uint32_t getRenderID() const { return m_OpenGL_ID; }
		inline uint32_t getDrawCount() { if (m_indexBuffer) { return m_indexBuffer->getCount(); } else { return 0; } }
		inline std::shared_ptr<IndexBuffer> getIndexBuffer() { return m_indexBuffer; }
	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		uint32_t m_attributeIndex = 0; //!< Attribute Index
		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffer;
		std::shared_ptr<IndexBuffer> m_indexBuffer;
	};
}