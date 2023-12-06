/** \file Renderer2D.h */
#pragma once
#include "rendering/RenderCommon.h"

namespace Engine
{

	class Quad
	{
	public:
		Quad() = default;
		static Quad createCentreHalf(const glm::vec2& centre, const glm::vec2& halfExents);
	private:
		glm::vec3 m_translate = glm::vec3(0.f); //<! Translation vector
		glm::vec3 m_scale = glm::vec3(1.f); //!< Scale vector
		friend class Renderer2D;
	};

	/** \class Renderer2D
	* \brief Class which allows the rendering of simple 2D primitives
	*/


	class Renderer2D
	{
	public:
		static void init(); //!< Init the internal data of the renderer
		static void begin(const SceneWideUniforms& swu); //!< Begin a new 2D scene
		static void submit(const Quad& quad, const glm::vec4& tint); //!< Render a tinted quad
		static void submit(const Quad& quad, const std::shared_ptr<OpenGLTexture>& texture); //!< Render a textured quad
		static void submit(const Quad& quad, const std::shared_ptr<OpenGLTexture>& texture, const glm::vec4& tint); //!< Render a textured and tint quad
		static void submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees = false); //!< Render a roatated and tint quad
		static void submit(const Quad& quad, const std::shared_ptr<OpenGLTexture>& texture, float angle, bool degrees = false); //!< Render a roatated and textured quad
		static void submit(const Quad& quad, const std::shared_ptr<OpenGLTexture>& texture, const glm::vec4& tint, float angle, bool degrees = false); //!< Render a roatated, textured and tint quad
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
