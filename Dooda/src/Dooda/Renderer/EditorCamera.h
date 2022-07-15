#pragma once

#include "Dooda/Core/Timestep.h"
#include "Dooda/Events/Event.h"
#include "Dooda/Events/MouseEvent.h"
#include "Dooda/Renderer/Camera.h"

#include <glm/glm.hpp>

namespace Dooda {

	class EditorCamera : public Camera
	{
	public:
		EditorCamera() = default;
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		inline float GetDistance() const { return d_Distance; }
		inline void SetDistance(float distance) { d_Distance = distance; }

		inline void SetViewportSize(float width, float height) { d_ViewportWidth = width; d_ViewportHeight = height; UpdateProjection(); }

		const glm::mat4& GetViewMatrix() const { return d_ViewMatrix; }
		glm::mat4 GetViewProjection() const { return d_Projection * d_ViewMatrix; }

		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;
		const glm::vec3& GetPosition() const { return d_Position; }
		glm::quat GetOrientation() const;

		float GetPitch() const { return d_Pitch; }
		float GetYaw() const { return d_Yaw; }
	private:
		void UpdateProjection();
		void UpdateView();

		bool OnMouseScroll(MouseScrolledEvent& e);

		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);
		void MouseZoom(float delta);

		glm::vec3 CalculatePosition() const;

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;
	private:
		float d_FOV = 45.0f, d_AspectRatio = 1.778f, d_NearClip = 0.1f, d_FarClip = 1000.0f;

		glm::mat4 d_ViewMatrix;
		glm::vec3 d_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 d_FocalPoint = { 0.0f, 0.0f, 0.0f };

		glm::vec2 d_InitialMousePosition = { 0.0f, 0.0f };

		float d_Distance = 10.0f;
		float d_Pitch = 0.0f, d_Yaw = 0.0f;

		float d_ViewportWidth = 1280, d_ViewportHeight = 720;
	};

}
