/** \file uniformBuffer.h*/
#pragma once

#include "RenderCommon.h"

namespace Engine
{
	class UniformBuffer
	{
	public:
	
		virtual ~UniformBuffer() = default; //!< Destuctor
		virtual uint32_t getRenderID() = 0;
		virtual UniformBufferLayout getLayout() = 0;
		virtual void attachShaderBlock(const std::shared_ptr<OpenGLShader>& shader, const char* blockName) = 0;
		virtual void uploadData(const char* uniformName, void* data) = 0;

	protected:
		UniformBufferLayout m_layout; //!< Uniform Buffer layout
		std::unordered_map<const char*, std::pair<uint32_t, uint32_t>> m_uniformCache; //!< Stores uniform names with offsets and sizes
		uint32_t m_blockNumber; //!< Block number for this UBO
	};
}
