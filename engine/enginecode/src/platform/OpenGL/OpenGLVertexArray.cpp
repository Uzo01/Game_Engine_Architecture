/* \ file OpenGLVertexArray */
#include "engine_pch.h"
#include <glad/glad.h>
#include "platform/OpenGL/OpenGLVertexArray.h"


namespace Engine
{
	namespace SDT
	{
		static GLenum toGLType(ShaderDataType type)
		{
			switch (type)
			{
				case ShaderDataType::Float: return GL_FLOAT;
				case ShaderDataType::Float2: return GL_FLOAT;
				case ShaderDataType::Float3: return GL_FLOAT;
				case ShaderDataType::Float4: return GL_FLOAT;
				default: return GL_INVALID_ENUM;

			}
		}
	}
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_OpenGL_ID);
		glBindVertexArray(m_OpenGL_ID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_OpenGL_ID);
	}
	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_OpenGL_ID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getRenderID());

		const auto& layout = vertexBuffer->getLayout();
		for (const auto& element : layout)
		{
			uint32_t normalised = GL_FALSE;
			if (element.m_normalised) { normalised = GL_TRUE; }
			glEnableVertexAttribArray(m_AttribIndex);
			glVertexAttribPointer(
				m_AttribIndex, SDT::componentCount (element.m_dataType),
				SDT::toGLType(element.m_dataType), normalised, layout.getStride(),
				(void*) element.m_offset); //!<Poisition
			m_AttribIndex++;
		}

		m_vertexBuffer.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<OpenGLIndexBuffer>& indexBuffer)
	{
		m_indexBuffer = indexBuffer;
	}
}