/** \file FreeOrthoCamera.cpp */

#include "engine_pch.h"
#include "cameras/FreeOrthoController.h"


namespace Engine
{
	FreeOthroController::FreeOthroController(const FreeOrthoParams& params)
	{
		m_rotationSpeed = params.rotationSpeed;
		m_translationSpeed = params.translationSpeed;
	}

	void FreeOthroController::onUpdate(float timestep)
	{
		if (InputPoller::isKeyPressed(NG_KEY_W))
		{
			m_position.x += -sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_position.y += cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
		}
		if (InputPoller::isKeyPressed(NG_KEY_S))
		{
			m_position.x -= -sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_position.y -= cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
		}
		if (InputPoller::isKeyPressed(NG_KEY_A))
		{
			m_position.x += cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_position.y += sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
		}
		if (InputPoller::isKeyPressed(NG_KEY_D))
		{
			m_position.x -= cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_position.y -= sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
		}
		if (InputPoller::isKeyPressed(NG_KEY_Q))
		{
			m_rotation -= timestep * m_rotationSpeed;
			if (m_rotation > 180.f) m_rotation -= 360.f;
			else if (m_rotation <= -180.f) m_rotation += 360.f;
		}
		if (InputPoller::isKeyPressed(NG_KEY_E))
		{
			m_rotation += timestep * m_rotationSpeed;
			if (m_rotation > 180.f) m_rotation -= 360.f;
			else if (m_rotation <= -180.f) m_rotation += 360.f;
		}

		glm::mat4 translation = glm::translate(glm::mat4(1.f), glm::vec3(m_position, 0.f));
		glm::mat4 rotation =  glm::rotate(glm::mat4(1.f), glm::radians(m_rotation), glm::vec3(0.f, 0.f, 1.f));
		m_model = translation * rotation;

		m_camera.updateView(m_model);
	}
	void FreeOthroController::onResize(WindowResizeEvent& e)
	{
		m_camera.projection = glm::ortho(0.f, static_cast<float>(e.getWidth()), static_cast<float>(e.getHeight()), 0.f);
	}
}