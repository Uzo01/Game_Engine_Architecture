/**\ FreeCameraEuler.cpp*/
#include "engine_pch.h"
#include "independent/camera/cameraControllerEuler.h"
#include "camera/cameraController.h"
#include "core/inputPoller.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <GLFW/glfw3.h>



namespace Engine
{
	cameraControllerEuler::cameraControllerEuler(const FPSEulerCameraProps& props)
	{
		//!< Set basic properties
		m_props = props;
		m_lastMousePos = glm::vec2(-1, 1);

		//Set models
		glm::mat4 rotX = glm::rotate(glm::mat4(1.f), m_props.pitch, glm::vec3(1.f, 0.f, 0.f));
		glm::mat4 rotY = glm::rotate(glm::mat4(1.f), m_props.yaw, glm::vec3(0.f, 1.f, 0.f));
		m_model = glm::translate(glm::mat4(1.f), m_props.position) * (rotX * rotY);

		//Set up camera matrices
		m_camera.projection = glm::perspective(glm::radians(m_props.fovY), m_props.aspectRation, m_props.nearClip, m_props.farClip);
		m_camera.updateView(m_model);

		//Set component vectors
		//Negative as camera faces back down the z axis
		m_forward = { -m_model[2][0], -m_model[2][1] ,-m_model[2][2] };
		m_up = { m_model[1][0], m_model[1][1], m_model[1][2] };
		m_right = { m_model[0][0], m_model[0][1], m_model[1][2] };

	}
	void cameraControllerEuler::onUpdate(float timestep)
	{
		bool camMoved = false;
		if (InputPoller::isKeyPressed(GLFW_KEY_W))
		{
			float y = m_props.position.y;
			m_props.position += m_forward * m_props.translationSpeed * timestep;
			m_props.position.y = y;
			camMoved = true;
		}
		if (InputPoller::isKeyPressed(GLFW_KEY_S))
		{
			float y = m_props.position.y;
			m_props.position -= m_forward * m_props.translationSpeed * timestep;
			m_props.position.y = y;
			camMoved = true;
		}
		if (InputPoller::isKeyPressed(GLFW_KEY_A))
		{
			
			m_props.position += m_right * m_props.translationSpeed * timestep;
			camMoved = true;
		}
		if (InputPoller::isKeyPressed(GLFW_KEY_D))
		{

			m_props.position -= m_right * m_props.translationSpeed * timestep;
			camMoved = true;
		}
		if (InputPoller::isMouseButonPressed(GLFW_MOUSE_BUTTON_RIGHT))
		{
			if (m_lastMousePos.x >= 0.f)
			{
				camMoved = true;
				glm::vec2 currentMousePosition = InputPoller::getMousePosition();
				glm::vec2 mouseDelta = currentMousePosition - m_lastMousePos;

				m_props.yaw -= mouseDelta.x * m_props.rotationSpeed * timestep;
				m_props.pitch -= mouseDelta.y * m_props.rotationSpeed * timestep;

				//Constrain pitch
				m_props.pitch = std::clamp(m_props.pitch,-89.f, 89.f);
			}
			m_lastMousePos = InputPoller::getMousePosition();
		}
		else
		{
			m_lastMousePos.x = 1.0f;
		}
		if (camMoved)
		{
			// Set Moved 
			glm::mat4 rotX = glm::rotate(glm::mat4(1.f), glm::radians(m_props.pitch), glm::vec3(1.f, 0.f, 0.f));
			glm::mat4 rotY = glm::rotate(glm::mat4(1.f), glm::radians(m_props.yaw), glm::vec3(0.f, 1.f, 0.f));
			m_model = glm::translate(glm::mat4(1.f), m_props.position) * (rotX * rotY);
			
			//Update acmera
			m_camera.updateView(m_model);

			//Update Components vectors
			m_forward = { -m_model[2][0], -m_model[2][1], -m_model[2][2] };
			m_up = { -m_model[1][0], -m_model[1][1], -m_model[1][2] };
			m_right = { -m_model[0][0], -m_model[0][1], -m_model[0][2] };
		}
		
	}

}



