/* \file OpenGLShader.h */
#pragma once

#include <cstdint>
#include <glm/glm.hpp>


namespace Engine {
	class OpenGLShader
	{
	public:
		OpenGLShader(const char* vertexFilePath, const char* fragmentFilePath); //!< Constructor which takes two file paths
		OpenGLShader(const char* filePath); //!< Constructor which take one filepath
		~OpenGLShader(); //!< Destructor
		uint32_t getID() const { return m_OpenGL_ID;  } //!< Returns OpenGL ID

		void uploadInt(const char* name, int value); //!< Uploads int
		void uploadIntArray(const char* name, int32_t* values, uint32_t count); //!< Uploads an array of ints
		void uploadFloat(const char* name, float value); //!< Uploads float
		void uploadFloat2(const char* name, const glm::vec2& value); //!< Uploads vec2
		void uploadFloat3(const char* name, const glm::vec3& value); //!< Uploads vec3
		void uploadFloat4(const char* name, const glm::vec4& value); //!< Uploads vec4
		void uploadMat4(const char* name, const glm::mat4& value); //!< Uploads mat4


	private:
		uint32_t m_OpenGL_ID; //!< OpenGL ID
		void compileAndLink(const char* vertexShaderSrc, const char* fragmentShaderSrc); //!< Compiles and links vertex and fragment shader
	};
}