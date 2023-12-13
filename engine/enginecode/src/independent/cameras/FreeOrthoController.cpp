/** \file FreeOrthoCamera.cpp */

#include "engine_pch.h"
#include "cameras/FreeOrthoController.h"


namespace Engine
{
	FreeOthroController::FreeOthroController(const FreeOrthoParams& params)
	{

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
	}
}