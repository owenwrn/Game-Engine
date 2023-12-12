#pragma once
#include <memory>
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLTexture.h"
#include "Renderer3D.h"
namespace Engine
{
	
	/** \class Material
* \brief Holds a shader and the uniform data associated with that shader
*/

	class Material
	{
	public:
		Material() = delete; //!< Delete the default constructor as all materials need a shader
		//! Constructor with shader only
		Material(const std::shared_ptr<OpenGLShader>& shader) :
			m_shader(shader), m_flags(0), m_texture(nullptr), m_tint(glm::vec4(0.f))
		{
		}
		//! Constructor with shader, texture, and tint
		Material(const std::shared_ptr<OpenGLShader>& shader, const std::shared_ptr<OpenGLTexture>& texture, const glm::vec4& tint) :
			m_shader(shader), m_texture(texture), m_tint(tint)
		{
			setFlag(flag_texture | flag_tint);
		}
		//! Constructor with shader, texture but no tint
		Material(const std::shared_ptr<OpenGLShader>& shader, const std::shared_ptr<OpenGLTexture>& texture) :
			m_shader(shader), m_texture(texture), m_tint(1.f, 1.f, 1.f, 1.f)
		{
			setFlag(flag_texture);
		}
		//! Constructor with shader, tint but no texture
		Material(const std::shared_ptr<OpenGLShader>& shader, const glm::vec4& tint) :
			m_shader(shader), m_texture(nullptr), m_tint(tint)
		{
			setFlag(flag_tint);
		}

		inline std::shared_ptr<OpenGLShader> getShader() const { return m_shader; } //!< Return the shader
		inline std::shared_ptr<OpenGLTexture> getTexture() const { return m_texture; } //!< Return the texture
		inline glm::vec4 getTint() const { return m_tint; } //!< Return the tint
		bool isFlagSet(uint32_t flag) const { return m_flags & flag; } //!< Check if a flag is checked

		void setTexture(const std::shared_ptr<OpenGLTexture>& texture) { m_texture = texture; setFlag(flag_texture); } //<! set the texture
		void setTexture(const glm::vec4& tint) { m_tint = tint; setFlag(flag_tint); } //<! set the tint

		constexpr static uint32_t flag_texture = 1 << 0; // 00000001
		constexpr static uint32_t flag_tint = 1 << 1;    // 00000010
	private:
		uint32_t m_flags = 0; //!< Bitfield representation of the shader settings
		std::shared_ptr<OpenGLShader> m_shader; //!< The material's shader
		std::shared_ptr<OpenGLTexture> m_texture; //!< The albedo texture to be applied to the material
		glm::vec4 m_tint; //!< Colour tint to be applied to some geometry
		void setFlag(uint32_t flag) { m_flags = m_flags | flag; } //!< Internal method to set a flag

	};
	
}