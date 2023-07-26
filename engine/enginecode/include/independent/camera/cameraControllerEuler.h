/* \cameraControllerEuler.h*/
#pragma once
#include "camera.h"
#include "camera/cameraController.h"
#include "camera/FPSEulerCameraProps.h"
#include "glm/glm.hpp"

/**\
* \Initialise with properties and store the properties
*/
namespace Engine
{
	class cameraControllerEuler:public CameraController
	{
	public:
		cameraControllerEuler(const FPSEulerCameraProps& props);
		void onUpdate(float timestep) override;
	private:
		FPSEulerCameraProps m_props;
		glm::mat4 m_model;
		glm::vec3 m_forward;
		glm::vec3 m_up;
		glm::vec3 m_right;
		glm::vec2 m_lastMousePos;
	};
}


