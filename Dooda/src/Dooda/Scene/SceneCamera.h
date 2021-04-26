#pragma once
#include "Dooda/Renderer/Camera.h"

namespace Dooda {

	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetOrthographic(float size, float nearClip, float farClip);

		void SetViewportSize(UINT width, UINT height);

		float GetOrthographicSize() const { return d_OrthographicSize; }
		void SetOrthographicSize(float size) { d_OrthographicSize = size; RecalculateProjection(); }
	private:
		void RecalculateProjection();
	private:
		float d_OrthographicSize = 10.0f;
		float d_OrthographicNear = -1.0f, d_OrthographicFar = 1.0f;

		float d_AspectRatio = 0.0f;
	};

}
