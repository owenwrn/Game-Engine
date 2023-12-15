/** \file Renderer2D.h */
#pragma once
#include "rendering/RenderCommon.h"
#include "platform/OpenGL/OpenGLUniformBuffer.h"
#include <array>

namespace Engine
{
	class Renderer2DVertex
	{
	public:
		Renderer2DVertex() = default;
		Renderer2DVertex(const glm::vec4& pos, const glm::vec2& UVs, uint32_t tu, const glm::vec4& pTint) :
			position(pos), uvCoords(UVs), texUnit(tu), tint(pack(pTint)) {}
		glm::vec4 position;
		glm::vec2 uvCoords;
		uint32_t texUnit;
		uint32_t tint;
		static VertexBufferLayout layout;
		static uint32_t pack(const glm::vec4& tint);
	};

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
		static void submit(const Quad& quad, const SubTexture& texture); //!< Render a textured quad
		static void submit(const Quad& quad, const SubTexture& texture, const glm::vec4& tint); //!< Render a textured and tint quad
		static void submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees = false); //!< Render a roatated and tint quad
		static void submit(const Quad& quad, const SubTexture& texture, float angle, bool degrees = false); //!< Render a roatated and textured quad
		static void submit(const Quad& quad, const SubTexture& texture, const glm::vec4& tint, float angle, bool degrees = false); //!< Render a roatated, textured and tint quad
		static void end(); //!< End the current 2D scene
		static void flush(); //!< Flush the current 2D scene

	private:

		struct InternalData
		{
			std::shared_ptr<OpenGLTexture> defaultTexture; //!< Empty white texture
			SubTexture defaultSubTexture; //!< Default SubTexture
			glm::vec4 defaultTint; //!< Default white tint
			std::shared_ptr<OpenGLShader> shader; //!< Shader
			std::shared_ptr<VertexArray> VAO; //!< Vertex array
			std::shared_ptr<OpenGLUniformBuffer> UBO; //!< uniform buffer object
			glm::mat4 model; //!< model
			std::array<glm::vec4, 4> quad; 
			static const uint32_t batchSize = 1024;//!< 2D RendererBatch Size
			uint32_t drawCount; //!< Draw count
			std::vector<Renderer2DVertex> vertices;
			std::array<int32_t, 32> textureUnits; //!< Texture unit
		};

		static std::shared_ptr<InternalData> s_data; //!< Data internal to the render

	};
}
