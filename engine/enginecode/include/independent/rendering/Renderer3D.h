/*\file Renderer3D.h */
#pragma once

#include "engine_pch.h"
#include "glm/glm.hpp"
#include "platform/OpenGL/vertexArray.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLTexture.h"
#include "rendering/shaderDataType.h"
#include <unordered_map>
#include "material.h"

namespace Engine
{
	/** \class Renderer3D
	** \brief A class which renders 3D geometry instantly (non-batched)
	*/ 
	using SceneWideUniforms = std::unordered_map<const char*, std::pair<ShaderDataType, void*>>;


	class Renderer3D
	{
	public:
		static void init(); //!< Init the renderer
		static void begin(const SceneWideUniforms& swu); //!< Begin a new 3D scene
		static void submit(const std::shared_ptr<VertexArray>& geometry, const Material& material, const glm::mat4& modelMat); //!< Submit a piece of geometry to be rendered
		static void end(); //!< End the current 3D scene

	private:

		struct InternalData
		{
			SceneWideUniforms swu; //!< Replace with UBO at some point
			std::shared_ptr<OpenGLTexture> defaultTexture; //!< Empty white texture
			glm::vec4 defaultTint; //!< Default white tint
		};

		static std::shared_ptr<InternalData> s_data; //!< Data internal to the render

	};

}
