#include "Ddpch.h"
#include "OrthographicCameraController.h"

#include "Dooda/Core/Input.h"
#include "Dooda/Core/KeyCodes.h"

namespace Dooda {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: d_AspectRatio(aspectRatio), d_Camera(-d_AspectRatio * d_ZoomLevel, d_AspectRatio* d_ZoomLevel, -d_ZoomLevel, d_ZoomLevel), d_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(DD_KEY_A))
		{
			d_CameraPosition.x -= cos(glm::radians(d_CameraRotation)) * d_CameraTranslationSpeed * ts;
			d_CameraPosition.y -= sin(glm::radians(d_CameraRotation)) * d_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(DD_KEY_D))
		{
			d_CameraPosition.x += cos(glm::radians(d_CameraRotation)) * d_CameraTranslationSpeed * ts;
			d_CameraPosition.y += sin(glm::radians(d_CameraRotation)) * d_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(DD_KEY_W))
		{
			d_CameraPosition.x += -sin(glm::radians(d_CameraRotation)) * d_CameraTranslationSpeed * ts;
			d_CameraPosition.y += cos(glm::radians(d_CameraRotation)) * d_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(DD_KEY_S))
		{
			d_CameraPosition.x -= -sin(glm::radians(d_CameraRotation)) * d_CameraTranslationSpeed * ts;
			d_CameraPosition.y -= cos(glm::radians(d_CameraRotation)) * d_CameraTranslationSpeed * ts;
		}

		if (d_Rotation)
		{
			if (Input::IsKeyPressed(DD_KEY_Q))
				d_CameraRotation += d_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(DD_KEY_E))
				d_CameraRotation -= d_CameraRotationSpeed * ts;

			if (d_CameraRotation > 180.0f)
				d_CameraRotation -= 360.0f;
			else if (d_CameraRotation <= -180.0f)
				d_CameraRotation += 360.0f;

			d_Camera.SetRotation(d_CameraRotation);
		}

		d_Camera.SetPosition(d_CameraPosition);

		d_CameraTranslationSpeed = d_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(DD_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(DD_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		d_ZoomLevel -= e.GetYOffset() * 0.25f;
		d_ZoomLevel = std::max(d_ZoomLevel, 0.25f);
		d_Camera.SetProjection(-d_AspectRatio * d_ZoomLevel, d_AspectRatio * d_ZoomLevel, -d_ZoomLevel, d_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		d_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		d_Camera.SetProjection(-d_AspectRatio * d_ZoomLevel, d_AspectRatio * d_ZoomLevel, -d_ZoomLevel, d_ZoomLevel);
		return false;
	}

}