/** \file OpenGLVertexBuffer.cpp*/

#include "engine_pch.h"
#include <glad/glad.h>
#include "platform\OpenGL\OpenGLVertexBuffer.h"


namespace Engine
{
	void BufferLayout::addElement(BufferElement element)
	{
		m_element.push_back(element);
		calcStrideAndOffset();
	}
	void BufferLayout::calcStrideAndOffset()
	{
		uint32_t l_offset = 0;

		for (auto& element : m_element)
		{
			element.m_offset = l_offset;
			l_offset += element.m_size;
		}
		m_stride = l_offset;
	}
	OpenGLVertexBuffer::OpenGLVertexBuffer::OpenGLVertexBuffer(void* vertices, uint32_t size, BufferLayout layout)
	{
		m_layout = layout;

		glCreateBuffers(1, &m_OpenGL_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_OpenGL_ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_OpenGL_ID);
	}

	void OpenGLVertexBuffer::OpenGLVertexBuffer::edit(void* vertices, uint32_t size, uint32_t offset)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_OpenGL_ID);
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
	}
}

