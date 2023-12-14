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