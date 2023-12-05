/** \file Renderer2D.h */
#pragma once
#include "rendering/RenderCommon.h"

namespace Engine
{

	class Quad;

	/** \class Renderer2D
	* \brief Class which allows the rendering of simple 2D primitives
	*/


	class Renderer2D
	{
	public:
		static void init(); //!< Init the internal data of the renderer
		static void begin(const SceneWideUniforms& swu); //!< Begin a new 2D scene
		static void submit(const Quad& quad, const glm::vec4& tint); //!< Render a tinted quad
		static void end(); //!< End the current 2D scene

	private:

		struct InternalData
		{
			std::shared_ptr<OpenGLTexture> defaultTexture; //!< Empty white texture
			glm::vec4 defaultTint; //!< Default white tint
			std::shared_ptr<OpenGLShader> shader;
			std::shared_ptr<VertexArray> VAO;
			glm::mat4 model;
		};

		static std::shared_ptr<InternalData> s_data; //!< Data internal to the render

	};
}
