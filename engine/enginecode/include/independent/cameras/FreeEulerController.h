/* \file FreeEulerController.h */
#pragma once

#include"camera.h"

namespace Engine
{
	struct FreeEulerParams
	{
		glm::vec3 position = glm::vec3(0.f);
		glm::vec3 rotation = glm::vec3(0.f);
		float fovY = 45.f;
		float speed = 2.5f;
		float sensitivity = 45.f;
		float aspectRatio = 4.f / 3.f;
		float nearClip = 0.1f;
		float farClip = 100.f;
		float ScrWidth;
		float ScrHeight;
	};
	class FreeEulerController : public CameraController
	{
	public:
		FreeEulerController(const FreeEulerParams& params);
		void onUpdate(float timestep) override;
		glm::vec3& getPosition() override { return m_position; }
	private:
		FreeEulerParams m_params;
		glm::vec3 m_position;
		glm::mat4 m_orientation;
		glm::mat4 m_transform;
		glm::vec2 m_lastMousePos;
		glm::vec3 m_rotation;
	};
}

