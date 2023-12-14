#include "OpenGLTest.h"

TEST(OpenGL, VertexArrayConstructor)
{
	//GLFW_GL_mock mock;
	Engine::VertexArray vao;

	uint32_t id = vao.getRenderID();

	EXPECT_EQ(id, 1);
}

TEST(OpenGL, VertexArrayBufferNull)
{
	Engine::VertexArray vao;

	uint32_t size = vao.getVertexBuffer().size();

	EXPECT_EQ(size, 0);
}

TEST(OpenGL, noIndexBufferCountNull)
{
	Engine::VertexArray vao;

	uint32_t count = vao.getDrawCount();

	EXPECT_EQ(count, 0);
}

TEST(OpenGL, UniformBufferConstructor)
{
	//GLFW_GL_mock mock;
	Engine::UniformBufferLayout layout = { { "u_projection", Engine::ShaderDataType::Mat4 }, { "u_view", Engine::ShaderDataType::Mat4 } };
	Engine::OpenGLUniformBuffer ubo(layout);

	uint32_t id = ubo.getRenderID();

	EXPECT_EQ(id, 1);


}