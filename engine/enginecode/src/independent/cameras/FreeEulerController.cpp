/** \file FreeEulerController.cpp */
#include "engine_pch.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include "events/events.h"
#include "cameras/FreeEulerController.h"
#include "platform/GLFW/inputPoller.h"



namespace Engine
{
	FreeEulerController::FreeEulerController(const FreeEulerParams& param)
	{


		m_lastMousePos = InputPoller::getMousePosition();
		m_camera.projection = glm::perspective(param.fovY, param.aspectRatio, param.nearClip, param.farClip);
	}

	void FreeEulerController::onUpdate(float timestep)
	{
		bool camMoved = false;
		if (InputPoller::isKeyPressed(NG_KEY_W))
		{
			float y = m_params.position.y;
			m_params.position += m_foward * m_params.translationSpeed * timestep;
			m_params.position.y = y;
			camMoved = true;
		}
		if (InputPoller::isKeyPressed(NG_KEY_S))
		{
			float y = m_params.position.y;
			m_params.position -= m_foward * m_params.translationSpeed * timestep;
			m_params.position.y = y;
			camMoved = true;
		}
		if (InputPoller::isKeyPressed(NG_KEY_A))
		{
			m_params.position -= m_right * m_params.translationSpeed * timestep;
			camMoved = true;
		}
		if (InputPoller::isKeyPressed(NG_KEY_D))
		{
			m_params.position += m_right * m_params.translationSpeed * timestep;
			camMoved = true;
		}

		if (InputPoller::isMouseButtonPressed(NG_MOUSE_BUTTON_RIGHT))
		{
			if (m_lastMousePos.x >= 0.f)
			{
				camMoved = true;
				glm::vec2 currentMousePos = InputPoller::getMousePosition();
				glm::vec2 mouseDelta = currentMousePos - m_lastMousePos;

				m_params.yaw -= mouseDelta.x * m_params.rotationSpeed * timestep;
				m_params.pitch -= mouseDelta.y * m_params.rotationSpeed * timestep;

				//m_params.pitch = std::clamp(m_params.pitch, -89.f, 89.f);
			}
			else
			{
				m_lastMousePos.x = -1.f;
			}
		}

		if (camMoved)
		{
			glm::mat4 rotX = glm::rotate(glm::mat4(1.f), m_params.pitch, glm::vec3(1.f, 0.f, 0.f));
			glm::mat4 rotY = glm::rotate(glm::mat4(1.f), m_params.yaw, glm::vec3(0.f, 1.f, 0.f));
			m_model = glm::translate(glm::mat4(1.f), m_params.position) * (rotX * rotY);

			m_camera.updateView(m_model);

			m_foward = { -m_model[2][0], -m_model[2][1], -m_model[2][2] };
			m_up = { m_model[1][0], m_model[1][1], m_model[1][2] };
			m_right = { m_model[0][0], m_model[0][1], m_model[0][2] };
		}
	}
}
