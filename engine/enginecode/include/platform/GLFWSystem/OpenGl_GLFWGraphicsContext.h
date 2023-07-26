#pragma once

#include "core/graphicsContext.h"
#include "GLFW/glfw3.h"

namespace Engine
{
	class OpenGl_GLFWGraphicsContext : GraphicsContext
	{
	public:
		OpenGl_GLFWGraphicsContext(GLFWwindow* window);
		void init() override;
		void swapBuffer() override;
	private:
		GLFWwindow* m_window;
	};

}
