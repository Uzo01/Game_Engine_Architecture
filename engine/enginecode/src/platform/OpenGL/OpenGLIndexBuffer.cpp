/* \file OpenGLIndexBuffer.cpp */
#include "engine_pch.h"
#include <glad/glad.h>
#include "platform/OpenGL/OpenGLIndexBuffer.h"


namespace Engine
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indicies, uint32_t count)
	{
		glCreateBuffers(1, &m_OpenGL_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_OpenGL_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) *count, indicies, GL_STATIC_DRAW);
		m_count = count;
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_OpenGL_ID);
	}
}