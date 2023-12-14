/** \file FixedOrthoController.h */
#pragma once

#include "camera.h"

namespace Engine
{
	struct FixedOrthoParams
	{
		glm::vec3 position = glm::vec3(0.f);
		float left;
		float right;
		float top;
		float bottom;
		float _near;
		float _far;
	};
	class FixedOthroController : public CameraController
	{
	public:
		FixedOthroController(const FixedOrthoParams& params) : m_position(params.position)
		{
			auto transform = glm::translate(glm::mat4(1.f), m_position);
			m_camera.view = glm::inverse(transform);
			m_camera.projection = glm::ortho(params.left, params.right, params.bottom, params.top);
		}
		glm::vec3& getPosition() override { return m_position;  }

	private:

		glm::vec3 m_position; //<! Position of the ortho projection

	};
}
