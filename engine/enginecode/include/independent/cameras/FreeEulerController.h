/* \file FreeEulerController.h */
#pragma once

#include"camera.h"

namespace Engine
{
	struct FreeEulerParams
	{
		glm::vec3 position = glm::vec3(0.f);
		float yaw = 0.f;
		float pitch = 0.f;
		float translationSpeed = 2.f;
		float rotationSpeed = 2.f;
		float fovY = 45.f;
		float aspectRatio = 16.f / 9.f;
		float nearClip = 0.1f;
		float farClip = 100.f;
	};
	class FreeEulerController : public CameraController
	{
	public:
		FreeEulerController(const FreeEulerParams& param);
		void onUpdate(float timestep) override;
	private:
		FreeEulerParams m_params;
		glm::mat4 m_model;
		glm::vec3 m_foward;
		glm::vec3 m_up;
		glm::vec3 m_right;
		glm::vec2 m_lastMousePos;

	};
}

