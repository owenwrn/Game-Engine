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
		FreeEulerController(const FreeEulerParams& params); //!< Constructor
		void onUpdate(float timestep) override; //!< Can update the camera
		glm::vec3& getPosition() override { return m_position; } //!< Get the camera position
	private:
		FreeEulerParams m_params;
		glm::vec3 m_position; //<! Position of camera
		glm::mat4 m_orientation; //<! Orientation of the camera
		glm::mat4 m_transform; //<! Camera transform
		glm::vec2 m_lastMousePos; //<! Last mouse position
		glm::vec3 m_rotation; //<! Camera rotation
	};
}

