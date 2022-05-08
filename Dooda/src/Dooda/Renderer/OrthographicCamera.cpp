#include "ddpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Dooda 
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: d_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), d_ViewMatrix(1.0f)
	{
		DD_PROFILE_FUNCTION();

		d_ViewProjectionMatrix = d_ProjectionMatrix * d_ViewMatrix;
	}

	OrthographicCamera::~OrthographicCamera()
	{
	}

	void OrthographicCamera::SetPosition(const glm::vec3& position)
	{
		DD_PROFILE_FUNCTION();

		d_Position = position; 
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetRotation(const float rotation)
	{
		DD_PROFILE_FUNCTION();

		d_Rotation = rotation * 57.3f;  //Make this work without the fixing?  57.3 works
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		DD_PROFILE_FUNCTION();

		d_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		d_ViewProjectionMatrix = d_ProjectionMatrix * d_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		DD_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), d_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(d_Rotation), glm::vec3 (0.0f, 0.0f, 1.0f));

		d_ViewMatrix = glm::inverse(transform);
		d_ViewProjectionMatrix = d_ProjectionMatrix * d_ViewMatrix;
	}

}