/** \file FreeOrthoController.h */
#pragma once

#include "camera.h"

namespace Engine
{
	struct FreeOrthoParams
	{
		glm::vec2 position = glm::vec2(0.f);
		glm::vec2 size = glm::vec2(1024.f, 800.f);
		float angle = 0.f;
		float translationSpeed = 100.f;
		float rotationSpeed = 0.f;
	};
	class FreeOthroController : public CameraController
	{
	public:
		FreeOthroController(const FreeOrthoParams& params);
		void onUpdate(float timestep) override;
		void onResize(WindowResizeEvent& e) override;

	private:
		glm::mat4 m_model;
		glm::vec2 m_position = glm::vec2(0.f);
		float m_rotation = 0.f;
		float m_translationSpeed = 100.f;
		float m_rotationSpeed = 10.f;
	};
}
