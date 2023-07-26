/**\file GLFWInputPoller.h*/
#pragma once
#include "engine_pch.h"
#include <glm/glm.hpp>
#include "platform/GLFWSystem/GLFWWindowImpl.h"

namespace Engine
{
	class GLFWInputPoller
	{
	public:
		static bool isKeyPressed(int32_t keyCode);//!< is key pressed 
		static bool isMouseButonPressed(int32_t mouseButton); //!< is mouse buton pressed 
		static glm::vec2 getMousePostion();//!< cut=rrent mouse postion
		static void setCurrentWindow(GLFWwindow* newWin) { s_window = newWin; }
	private:
		static GLFWwindow* s_window;//!< Current GLFW window
	};
}