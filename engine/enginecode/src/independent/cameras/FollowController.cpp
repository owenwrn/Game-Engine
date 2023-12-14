/** \file FollowController.cpp */
#include "engine_pch.h"
#include "cameras/FollowController.h"

namespace Engine
{
	FollowController::FollowController(const FollowParams& params)
	{
		m_entityTransform = params.entityTransform;
		m_offset = params.offset;

		glm::vec3 right = { (*m_entityTransform)[0][0], (*m_entityTransform)[0][1],(*m_entityTransform)[0][2] };
		glm::vec3 up = { (*m_entityTransform)[1][0], (*m_entityTransform)[1][1],(*m_entityTransform)[1][2] };
		glm::vec3 foward = { (*m_entityTransform)[2][0], (*m_entityTransform)[2][1],(*m_entityTransform)[2][2] };
		m_entityPosition = { (*m_entityTransform)[3][0], (*m_entityTransform)[3][1],(*m_entityTransform)[3][2] };

		glm::vec3 posDelta(0.f);
		posDelta += foward * -m_offset.z;
		posDelta += right * m_offset.x;
		posDelta += up * m_offset.y;

		m_position = m_entityPosition + posDelta;
		glm::vec3 camFoward = -posDelta;
		glm::vec3 camRight = glm::cross({ 0,1,0 },posDelta);
		glm::vec3 camUp = glm::normalize(glm::cross(camRight, camFoward));

		m_camera.view = glm::lookAt(m_position, m_entityPosition, camUp);
		m_camera.projection = glm::perspective(params.fovY, params.aspectRatio, params.nearClip, params.farClip);
	}
	void FollowController::onUpdate(float timestep)
	{
		glm::vec3 right = { (*m_entityTransform)[0][0], (*m_entityTransform)[0][1],(*m_entityTransform)[0][2] };
		glm::vec3 up = { (*m_entityTransform)[1][0], (*m_entityTransform)[1][1],(*m_entityTransform)[1][2] };
		glm::vec3 foward = { (*m_entityTransform)[2][0], (*m_entityTransform)[2][1],(*m_entityTransform)[2][2] };
		m_entityPosition = { (*m_entityTransform)[3][0], (*m_entityTransform)[3][1],(*m_entityTransform)[3][2] };

		glm::vec3 posDelta(0.f);
		posDelta += foward * -m_offset.z;
		posDelta += right * m_offset.x;
		posDelta += up * m_offset.y;

		m_position = m_entityPosition + posDelta;
		glm::vec3 camFoward = -posDelta;
		glm::vec3 camRight = glm::cross({ 0,1,0 }, posDelta);
		glm::vec3 camUp = glm::normalize(glm::cross(camRight, camFoward));

		m_camera.view = glm::lookAt(m_position, m_entityPosition, camUp);
	}
}