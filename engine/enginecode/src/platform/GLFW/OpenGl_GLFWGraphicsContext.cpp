#include "engine_pch.h"
#include "glad/glad.h"
#include "platform\GLFWSystem\OpenGl_GLFWGraphicsContext.h"
#include "systems/log.h"


namespace Engine
{
	Engine::OpenGl_GLFWGraphicsContext::OpenGl_GLFWGraphicsContext(GLFWwindow* window)
	{
		m_window = window;
	}

	void Engine::OpenGl_GLFWGraphicsContext::init()
	{
		glfwMakeContextCurrent(m_window);
		int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if(!result) Log::error("Failed to initialise GLAD");
	}

	void Engine::OpenGl_GLFWGraphicsContext::swapBuffer()
	{
		glfwSwapBuffers(m_window);
	}
}


