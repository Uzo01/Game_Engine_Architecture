#pragma once

#include "include/platform/GLFWSystem/GLFWSystem.h"
#include "include/platform/GLFWSystem/GLFWWindowImpl.h"


class GLFW_GL_mock
{
public:
	GLFW_GL_mock();//!< constructor 
	~GLFW_GL_mock();//!< default Constructor
	std::shared_ptr<Engine::System> glfwSystem; //!< shared pointer to glfw system
	std::shared_ptr<Engine::Window> glfwWindow;//!< shared pointer to glfw window
};

