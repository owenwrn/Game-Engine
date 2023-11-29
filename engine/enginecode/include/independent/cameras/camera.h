/* \file camera.h */
#pragma once
#include "engine_pch.h"
#include <glm/glm.hpp>

namespace Engine
{
	/** \class Camera
	* \brief Basic Camera base class
	*/
	class Camera
	{
	public:
		glm::mat4 view; //!< View matrix of the camera
		glm::mat4 projection; //!< Projection matrix of the camera
		void updateView(const glm::mat4& transform) //!< Update the view matrix as an inverse of a model (transform) matrix
		{
			view = glm::inverse(transform);
		}
	};

	class CameraController
	{
	public: 
		virtual Camera& getCamera() { return m_camera; } //!< Accessor for camera
		virtual void onUpdate(float t) {}; //!< Can update the camera
		virtual glm::vec3& getPosition() = 0;  //!< Get the camera position
	protected:
		Camera m_camera; //!< Camera being controlled
	};
}