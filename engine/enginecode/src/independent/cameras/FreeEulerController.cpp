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
	FreeEulerController::FreeEulerController(const FreeEulerParams& params)
	{
		m_position = params.position;
		m_rotation = params.rotation;

		m_lastMousePos = InputPoller::getMousePosition();
		m_camera.view = glm::lookAt(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f, 1.f, 0.f)
		);
		m_camera.projection = glm::perspective(params.fovY, params.aspectRatio, params.nearClip, params.farClip);
	}

	void FreeEulerController::onUpdate(float timestep)
	{
		float speed = 2.5f;
		float sensitivity = 45.f;

		glm::vec3 right = { m_transform[0][0], m_transform[0][1], m_transform[0][2] };
		glm::vec3 foward = { -m_transform[2][0], -m_transform[2][1], -m_transform[2][2] };
	
		if (InputPoller::isKeyPressed(NG_KEY_W))
		{
			m_position += (foward * speed * timestep);
		}
		if (InputPoller::isKeyPressed(NG_KEY_S)) m_position -= (foward * speed * timestep);
		
		if (InputPoller::isKeyPressed(NG_KEY_A)) m_position -= (right * speed * timestep);
		if (InputPoller::isKeyPressed(NG_KEY_D))m_position += (right * speed * timestep);

		if (InputPoller::isKeyPressed(NG_KEY_UP)) m_rotation.x +=  speed * timestep;
		if (InputPoller::isKeyPressed(NG_KEY_DOWN)) m_rotation.x -= speed * timestep;
		
		if (InputPoller::isKeyPressed(NG_KEY_LEFT)) m_rotation.y += speed * timestep;
		if (InputPoller::isKeyPressed(NG_KEY_RIGHT)) m_rotation.y -= speed * timestep;

		if (InputPoller::isKeyPressed(NG_KEY_E)) m_rotation.z += speed * timestep;
		if (InputPoller::isKeyPressed(NG_KEY_Q)) m_rotation.z -= speed * timestep;
		
		glm::vec2 currentMousePos = InputPoller::getMousePosition();
		glm::vec2 deltaMousePos = currentMousePos - m_lastMousePos;
		deltaMousePos /= glm::vec2(800.f, 600.f);
		m_rotation.y -= sensitivity * deltaMousePos.x * timestep;
		m_rotation.x -= sensitivity * deltaMousePos.y * timestep;

		m_lastMousePos = currentMousePos;

		glm::mat4 rotX = glm::rotate(glm::mat4(1.f), m_rotation.x, glm::vec3(1.f, 0.f, 0.f));
		glm::mat4 rotY = glm::rotate(glm::mat4(1.f), m_rotation.x, glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 rotZ = glm::rotate(glm::mat4(1.f), m_rotation.x, glm::vec3(0.f, 0.f, 1.f));

		m_orientation = rotX * rotY * rotZ;

		m_transform = glm::translate(glm::mat4(1.f), m_position) * m_orientation;

		m_camera.updateView(m_transform);
	}
}
