/* \FPSEulercameraProps.h*/
#pragma once
#include "glm/glm.hpp"
/**\
* \Initialise with properties and store the properties
*/

namespace Engine
{
	struct  FPSEulerCameraProps
	{
		glm::vec3 position = glm::vec3(0.f);
		float yaw = 0.f;
		float pitch = 0.f;
		float translationSpeed = 2.0f;
		float rotationSpeed = 2.f;
		float fovY = 45.f;
		float aspectRation = 16.f / 9.f;
		float nearClip = 0.1f;
		float farClip = 100.f;
	};
}
