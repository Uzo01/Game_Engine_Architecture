#include "OpenGLTest.h"

TEST(OpenGL, VertexArrayConstructor)
{
	GLFW_GL_mock  mock;
	Engine::OpenGLVertexArray vao;

	uint32_t id = vao.getRenderID();

	EXPECT_EQ(id, 1);
}
TEST(OpenGL, VertexArrayBufferNull)
{
	GLFW_GL_mock  mock;
	Engine::OpenGLVertexArray vao;

	uint32_t size = vao.getDrawCount();

	EXPECT_EQ(size, 0);
}
