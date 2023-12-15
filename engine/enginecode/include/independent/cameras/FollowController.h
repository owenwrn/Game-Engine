/* \file FollowController.h */
#pragma once

#include"camera.h"

namespace Engine
{
	struct FollowParams
	{
		glm::mat4* entityTransform;
		float fovY = 45.f;
		float aspectRatio = 4.f / 3.f;
		float nearClip = 0.1f;
		float farClip = 100.f;
		glm::vec3 offset;
	};
	class FollowController : public CameraController
	{
	public:
		FollowController(const FollowParams& params); //!< Constructor
		void onUpdate(float timestep) override; //!< Can update the camera
		glm::vec3& getPosition() override { return m_position; } //!< Get the camera position
		glm::vec3& getEntityPosition() { return m_entityPosition; } //!< Get the Entities position
	private:
		glm::vec3 m_position; //<! camera position
		glm::vec3 m_entityPosition; //!< Entities position
		glm::mat4* m_entityTransform; //!< Transform to follow
		glm::vec3 m_offset; //!< offset to follow oat
	};
}
