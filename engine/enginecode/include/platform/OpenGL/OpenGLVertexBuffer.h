/** \file OpenGlVertextBuffer */
#pragma once

#include "rendering/bufferLayout.h"

namespace Engine 
{
	class OpenGLVertexBuffer
	{
	public: 
		OpenGLVertexBuffer(void* vertices, uint32_t size, BufferLayout layout); //!< Constructor
		~OpenGLVertexBuffer();//!< default constructor
		void edit(void* vertices, uint32_t size, uint32_t offset);
		inline uint32_t getRenderID() const { return m_OpenGL_ID; }
		inline const BufferLayout& getLayout() const { return m_layout; }
	private:
		uint32_t m_OpenGL_ID; //!< Renderer ID
		BufferLayout m_layout;
	};
}