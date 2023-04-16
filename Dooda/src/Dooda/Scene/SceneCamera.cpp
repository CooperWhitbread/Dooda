#include "ddpch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Dooda 
{

	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetPerspective(float verticalFOV, float nearClip, float farClip)
	{
		d_ProjectionType = ProjectionType::Perspective;
		d_PerspectiveFOV = verticalFOV;
		d_PerspectiveNear = nearClip;
		d_PerspectiveFar = farClip;
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		d_ProjectionType = ProjectionType::Orthographic;
		d_OrthographicSize = size;
		d_OrthographicNear = nearClip;
		d_OrthographicFar = farClip;
		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		DD_CORE_ASSERT(width > 0 && height > 0);
		d_AspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		if (d_ProjectionType == ProjectionType::Perspective)
		{
			d_Projection = glm::perspective(d_PerspectiveFOV, d_AspectRatio, d_PerspectiveNear, d_PerspectiveFar);
		}
		else
		{
			float orthoLeft = -d_OrthographicSize * d_AspectRatio * 0.5f;
			float orthoRight = d_OrthographicSize * d_AspectRatio * 0.5f;
			float orthoBottom = -d_OrthographicSize * 0.5f;
			float orthoTop = d_OrthographicSize * 0.5f;

			d_Projection = glm::ortho(orthoLeft, orthoRight,
				orthoBottom, orthoTop, d_OrthographicNear, d_OrthographicFar);
		}
	}
}
