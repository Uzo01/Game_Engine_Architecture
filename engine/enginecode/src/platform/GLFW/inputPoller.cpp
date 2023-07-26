/**\ file inputPoller.cpp*/

#include "engine_pch.h"
#include "core/inputPoller.h"
#include "platform/GLFWSystem/GLFWInputPoller.h"
#ifdef NG_PLATFORM_WINDOWS
namespace Engine
{
	bool InputPoller::isKeyPressed(int keyCode)
	{
		return GLFWInputPoller::isKeyPressed(keyCode);
	}

	bool InputPoller::isMouseButonPressed(int button)
	{
		return GLFWInputPoller::isMouseButonPressed(button);
	}

	glm::vec2 InputPoller::getMousePosition()
	{
		return GLFWInputPoller::getMousePostion();
	}

	void InputPoller::setCurrentWindow(void* newWin)
	{
		GLFWInputPoller::setCurrentWindow((GLFWwindow*)newWin);
	}
}

#endif