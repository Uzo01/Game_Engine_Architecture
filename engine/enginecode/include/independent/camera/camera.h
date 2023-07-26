/* \camera.h*/
#pragma once

#include "glm/glm.hpp"
/** \camera class
	\Basic camera class
*/

namespace Engine {
	class Camera
	{
	public:
		glm::mat4 view; //!< View matrix of the camera 
		glm::mat4 projection; //!<Projection matrix of the camera
		void updateView(const glm::mat4& transform)//!< Update the view matrix as an inverse of a model (transform) matrix
		{
			view = glm::inverse(transform);
		}
	};
}
