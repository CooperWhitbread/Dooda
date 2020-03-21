#pragma once

#include "Dooda/Renderer/OrthographicCamera.h"
#include "Dooda/Core/Timestep.h"

#include "Dooda/Events/ApplicationEvent.h"
#include "Dooda/Events/MouseEvent.h"

namespace Dooda {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);
		~OrthographicCameraController() = default;

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

	public: //Getters
		OrthographicCamera& GetCamera() { return d_Camera; }
		const OrthographicCamera& GetCamera() const { return d_Camera; }

		float GetZoomLevel() const { return d_ZoomLevel; }

	public: //Setters
		void SetZoomLevel(float level) { d_ZoomLevel = level; }

	private: //Private Functions
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private: //Variables
		float d_AspectRatio;
		float d_ZoomLevel = 1.0f;
		OrthographicCamera d_Camera;

		bool d_Rotation; 

		glm::vec3 d_CameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		float d_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float d_CameraTranslationSpeed = 5.0f;
		float d_CameraRotationSpeed = 180.0f;
	};

}