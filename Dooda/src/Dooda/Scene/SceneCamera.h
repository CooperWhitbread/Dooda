#pragma once

#include "Dooda/Renderer/Camera.h"

namespace Dooda 
{

	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetPerspective(float verticalFOV, float nearClip, float farClip);
		void SetOrthographic(float size, float nearClip, float farClip);

		void SetViewportSize(UINT width, UINT height);

		float GetPerspectiveVerticalFOV() const { return d_PerspectiveFOV; }
		void SetPerspectiveVerticalFOV(float verticalFov) { d_PerspectiveFOV = verticalFov; RecalculateProjection(); }
		float GetPerspectiveNearClip() const { return d_PerspectiveNear; }
		void SetPerspectiveNearClip(float nearClip) { d_PerspectiveNear = nearClip; RecalculateProjection(); }
		float GetPerspectiveFarClip() const { return d_PerspectiveFar; }
		void SetPerspectiveFarClip(float farClip) { d_PerspectiveFar = farClip; RecalculateProjection(); }

		float GetOrthographicSize() const { return d_OrthographicSize; }
		void SetOrthographicSize(float size) { d_OrthographicSize = size; RecalculateProjection(); }
		float GetOrthographicNearClip() const { return d_OrthographicNear; }
		void SetOrthographicNearClip(float nearClip) { d_OrthographicNear = nearClip; RecalculateProjection(); }
		float GetOrthographicFarClip() const { return d_OrthographicFar; }
		void SetOrthographicFarClip(float farClip) { d_OrthographicFar = farClip; RecalculateProjection(); }

		ProjectionType GetProjectionType() const { return d_ProjectionType; }
		void SetProjectionType(ProjectionType type) { d_ProjectionType = type; RecalculateProjection(); }
	private:
		void RecalculateProjection();
	private:
		ProjectionType d_ProjectionType = ProjectionType::Orthographic;

		float d_PerspectiveFOV = glm::radians(45.0f);
		float d_PerspectiveNear = 0.01f, d_PerspectiveFar = 1000.0f;

		float d_OrthographicSize = 10.0f;
		float d_OrthographicNear = -1.0f, d_OrthographicFar = 1.0f;

		float d_AspectRatio = 0.0f;
	};

}
