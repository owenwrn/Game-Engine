/* \file Renderer2D.cpp*/

#include "engine_pch.h"
#include <glad/glad.h>
#include "rendering/Renderer2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <numeric>


namespace Engine
{
	TextureUnitManager RenderCommon::texUnitManager = TextureUnitManager(32);

	VertexBufferLayout Renderer2DVertex::layout = VertexBufferLayout({ ShaderDataType::Float4, ShaderDataType::Float2, ShaderDataType::FlatInt, {ShaderDataType::Byte4, true} });

	std::shared_ptr<Renderer2D::InternalData> Renderer2D::s_data = nullptr;

	void Renderer2D::init()
	{
		s_data.reset(new InternalData);

		unsigned char whitePx[4] = { 255, 255, 255,255 };
		s_data->defaultTexture.reset(new OpenGLTexture(1, 1, 4, whitePx));

		s_data->defaultSubTexture = SubTexture(s_data->defaultTexture, { 0.f, 0.f }, { 1.f, 1.f });

		s_data->defaultTint = { 1.f, 1.f, 1.f, 1.f };

		s_data->model = glm::mat4(1.f);

		s_data->textureUnits = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12 ,13, 14, 15, 16, 17, 18, 19 ,20 ,21, 22 ,23 ,24 ,25 ,26 ,27, 28, 29, 30, 31 };

		s_data->shader.reset(new OpenGLShader("./assets/shaders/quad3.vert", "./assets/shaders/quad3.frag"));

		s_data->UBO.reset(new OpenGLUniformBuffer(UniformBufferLayout({ {"u_projection", ShaderDataType::Mat4},  {"u_view", ShaderDataType::Mat4} })));

		s_data->quad[0] = { -0.5f, -0.5f, 1.f, 1.f };
		s_data->quad[1] = { -0.5f,  0.5f, 1.f, 1.f };
		s_data->quad[2] = { 0.5f,  0.5f, 1.f, 1.f };
		s_data->quad[3] = { 0.5f, -0.5f, 1.f, 1.f };

		s_data->vertices.resize(s_data->batchSize * 4);
		/*s_data->vertices[0] = Renderer2DVertex(s_data->quad[0], {0.f, 0.f}, 0, glm::vec4(1.f));
		s_data->vertices[1] = Renderer2DVertex(s_data->quad[1], { 0.f, 1.f }, 0, glm::vec4(1.f));
		s_data->vertices[2] = Renderer2DVertex(s_data->quad[2], { 1.f, 1.f }, 0, glm::vec4(1.f));
		s_data->vertices[3] = Renderer2DVertex(s_data->quad[3], { 1.f, 0.f }, 0, glm::vec4(1.f));*/

		std::vector<uint32_t> indices(s_data->batchSize * 4);
		std::iota(indices.begin(), indices.end(), 0);

		std::shared_ptr<VertexBuffer> VBO;
		std::shared_ptr<IndexBuffer> IBO;
		s_data->VAO.reset(new VertexArray());
		VBO.reset(new VertexBuffer(s_data->vertices.data(), sizeof(Renderer2DVertex)* s_data->vertices.size(), Renderer2DVertex::layout));
		IBO.reset(new IndexBuffer(indices.data(), indices.size()));
		s_data->VAO->addVertexBuffer(VBO);
		s_data->VAO->setIndexBuffer(IBO);

		s_data->UBO->attachShaderBlock(s_data->shader, "b_camera");
	}

	void Renderer2D::begin(const SceneWideUniforms& swu)
	{
		s_data->drawCount = 0;

		glUseProgram(s_data->shader->getID());

		s_data->shader->uploadIntArray("u_texData", s_data->textureUnits.data(), 32);

		glBindBuffer(GL_UNIFORM_BUFFER, s_data->UBO->getRenderID());
		s_data->UBO->uploadData("u_projection", swu.at("u_projection").second);
		s_data->UBO->uploadData("u_view", swu.at("u_view").second);

		//bind geometry
		//glBindVertexArray(s_data->VAO->getRenderID());
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIndexBuffer()->getRenderID());
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint)
	{
		Renderer2D::submit(quad, s_data->defaultSubTexture, tint);
	}

	void Renderer2D::submit(const Quad& quad, const SubTexture& texture)
	{
		Renderer2D::submit(quad, texture, s_data->defaultTint);
	}

	void Renderer2D::submit(const Quad& quad, const SubTexture& texture, const glm::vec4& tint)
	{
		if (s_data->drawCount + 4 > s_data->batchSize * 4) flush();

		uint32_t texUnit;
		if (RenderCommon::texUnitManager.full()) flush();
		if (RenderCommon::texUnitManager.getUnit(texture.getBaseTexture()->getID(), texUnit))
		{
			glActiveTexture(GL_TEXTURE0 + texUnit);
			glBindTexture(GL_TEXTURE_2D, texture.getBaseTexture()->getID());
		}		
		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_translate), quad.m_scale);

		uint32_t packedTint = Renderer2DVertex::pack(tint);
		
		uint32_t startIdx = s_data->drawCount;
		for (int i = 0; i < 4; i++)
		{
			s_data->vertices[i + startIdx].position = s_data->model * s_data->quad[i];
			s_data->vertices[i + startIdx].tint = packedTint;
			s_data->vertices[i + startIdx].texUnit = texUnit;
		}
		s_data->vertices[startIdx + 0].uvCoords = texture.getUVStart();
		s_data->vertices[startIdx + 1].uvCoords = { texture.getUVStart().x, texture.getUVEnd().y };
		s_data->vertices[startIdx + 2].uvCoords = texture.getUVEnd();
		s_data->vertices[startIdx + 3].uvCoords = { texture.getUVEnd().x, texture.getUVStart().y };

		s_data->drawCount += 4;

		/*s_data->VAO->getVertexBuffer().at(0)->edit(s_data->vertices.data(), sizeof(Renderer2DVertex) * s_data->vertices.size(), 0);

		glBindVertexArray(s_data->VAO->getRenderID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIndexBuffer()->getRenderID());

		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);*/
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees)
	{
		Renderer2D::submit(quad, s_data->defaultSubTexture, tint, angle, degrees);
	}

	void Renderer2D::submit(const Quad& quad, const SubTexture& texture, float angle, bool degrees)
	{
		Renderer2D::submit(quad, texture, s_data->defaultTint, angle, degrees);
	}

	void Renderer2D::submit(const Quad& quad, const SubTexture& texture, const glm::vec4& tint, float angle, bool degrees)
	{
		if (s_data->drawCount + 4 > s_data->batchSize * 4) flush();

		if (degrees) angle = glm::radians(angle);

		uint32_t texUnit;
		if (RenderCommon::texUnitManager.getUnit(texture.getBaseTexture()->getID(), texUnit))
		{
			glActiveTexture(GL_TEXTURE0 + texUnit);
			glBindTexture(GL_TEXTURE_2D, texture.getBaseTexture()->getID());
		}
		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_translate), quad.m_scale);

		uint32_t packedTint = Renderer2DVertex::pack(tint);

		uint32_t startIdx = s_data->drawCount;
		for (int i = 0 ; i < 4; i++)
		{
			s_data->vertices[i + startIdx].position = s_data->model * s_data->quad[i];
			s_data->vertices[i + startIdx].tint = packedTint;
			s_data->vertices[i + startIdx].texUnit = texUnit;
		}
		s_data->vertices[startIdx + 0].uvCoords = texture.getUVStart();
		s_data->vertices[startIdx + 1].uvCoords = { texture.getUVStart().x, texture.getUVEnd().y };
		s_data->vertices[startIdx + 2].uvCoords = texture.getUVEnd();
		s_data->vertices[startIdx + 3].uvCoords = { texture.getUVEnd().x, texture.getUVStart().y };

		s_data->drawCount += 4;
	}

	void Renderer2D::end()
	{
		if (s_data->drawCount > 0) flush();
	}

	void Renderer2D::flush()
	{
		s_data->VAO->getVertexBuffer().at(0)->edit(s_data->vertices.data(), sizeof(Renderer2DVertex) * s_data->drawCount, 0);

		glBindVertexArray(s_data->VAO->getRenderID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIndexBuffer()->getRenderID());

		glDrawElements(GL_QUADS, s_data->drawCount, GL_UNSIGNED_INT, nullptr);

		s_data->drawCount = 0;
	}

	Quad Quad::createCentreHalf(const glm::vec2& centre, const glm::vec2& halfExents)
	{
		Quad result;

		result.m_translate = glm::vec3(centre, 0.f);
		result.m_scale = glm::vec3(halfExents * 2.f, 1.f);

		return result;
	}
	uint32_t Renderer2DVertex::pack(const glm::vec4& tint)
	{

		uint32_t result = 0;

		uint32_t r = (static_cast<uint32_t>(tint.r * 255.f)) << 0;
		uint32_t g = (static_cast<uint32_t>(tint.g * 255.f)) << 8;
		uint32_t b = (static_cast<uint32_t>(tint.b * 255.f)) << 16;
		uint32_t a = (static_cast<uint32_t>(tint.a * 255.f)) << 24;

		result = (r | g | b | a);
		return result;
	}
}