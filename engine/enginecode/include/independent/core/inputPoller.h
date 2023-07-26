/**\file inputPoller.h*/
#pragma once
#include "engine_pch.h"
#include<glm/glm.hpp>

namespace Engine
{
	/**
	* class API anosticclass for direct polling of input
	*/

	class InputPoller
	{
	public:
		static bool isKeyPressed(int keycode);//!< check for keycode pressed
		static bool isMouseButonPressed(int button); //!< Is mouse button pressed
		static glm::vec2 getMousePosition(); //!< get current position of mouse
		inline static float getMouseX() { return getMousePosition().x; }//!<get postion of mouse on x axis
		inline static float getMouseY() { return getMousePosition().y; }//!< get mouse postion on the y axis
		static void setCurrentWindow(void* newWin);//!< Set to current window
	};
}