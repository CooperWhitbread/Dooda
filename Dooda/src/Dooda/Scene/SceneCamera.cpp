#include "Ddpch.h"
#include "SceneCamera.h"


#include <glm/gtc/matrix_transform.hpp>

namespace Dooda {

	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		d_OrthographicSize = size;
		d_OrthographicNear = nearClip;
		d_OrthographicFar = farClip;
		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(UINT width, UINT height)
	{
		d_AspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		float orthoLeft = -d_OrthographicSize * d_AspectRatio * 0.5f;
		float orthoRight = d_OrthographicSize * d_AspectRatio * 0.5f;
		float orthoBottom = -d_OrthographicSize * 0.5f;
		float orthoTop = d_OrthographicSize * 0.5f;

		d_Projection = glm::ortho(orthoLeft, orthoRight,
			orthoBottom, orthoTop, d_OrthographicNear, d_OrthographicFar);
	}
}
