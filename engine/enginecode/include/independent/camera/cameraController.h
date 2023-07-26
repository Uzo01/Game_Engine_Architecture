/* \cameraController.h*/
#pragma once
#include "glm/glm.hpp"
#include "events/windowEvents.h"

/** \camera class
	\Basic camera class controller
*/

namespace Engine {
	class CameraController
	{
	public:
		Camera& getCamera() { return m_camera; }
		virtual void onUpdate(float t) {};
		virtual void onResize(Engine::WindowResizeEvent& e) {};
	protected:
		Camera m_camera;

	};
}

	
