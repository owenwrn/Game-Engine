/** \file RenderCommon.h */
#pragma once

#include <glm/glm.hpp>
#include "platform/OpenGL/vertexArray.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLTexture.h"
#include "rendering/shaderDataType.h"
#include <unordered_map>
#include <memory>

namespace Engine
{
	using SceneWideUniforms = std::unordered_map<const char*, std::pair<ShaderDataType, void*>>;
}