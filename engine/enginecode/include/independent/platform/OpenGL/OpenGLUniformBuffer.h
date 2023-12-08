/** \file OpenGLUniformBuffer.h */
#pragma once

#include "rendering/bufferLayout.h"
#include "rendering/RenderCommon.h"

namespace Engine
{
	class OpenGLUniformBuffer
	{
	public:
		OpenGLUniformBuffer(const UniformBufferLayout& layout); //!< Constructor
		~OpenGLUniformBuffer(); //!< Destuctor
		inline uint32_t getRenderID() { return m_OpenGL_ID;  }
		inline UniformBufferLayout getLayout() { return m_layout;  }
		void attachShaderBlock(const std::shared_ptr<OpenGLShader>& shader, const char* blockName);
		void uploadData(const char* uniformName, void* data);

		//TODO renderAPI
		//static UniformBuffer* create(const UniformBufferLayout& layout);

	private:
		uint32_t m_OpenGL_ID; //!< OpenGL ID
		UniformBufferLayout m_layout; //!< Uniform Buffer layout
		std::unordered_map<const char*, std::pair<uint32_t, uint32_t>> m_uniformCache; //!< Stores uniform names with offsets and sizes
		uint32_t m_blockNumber; //!< Block number for this UBO
		static uint32_t s_blockNumber; //!< Global block number
	};
}