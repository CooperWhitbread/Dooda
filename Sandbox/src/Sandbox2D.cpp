#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	DD_PROFILE_FUNCTION();

	Dooda::Texture2DManager::Create();
	Dooda::s_Texture2DManager->AddTexture("assets/textures/Checkerboard.png", "CheckerBoard");
}

void Sandbox2D::OnDetach()
{
	DD_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Dooda::Timestep ts)
{
	DD_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	{
		DD_PROFILE_SCOPE("Renderer Prep");
		Dooda::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Dooda::RenderCommand::Clear();
	}

	{
		DD_PROFILE_SCOPE("Renderer Draw");
		Dooda::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Dooda::Renderer2D::DrawRotatedQuad(glm::vec2(-1.0f, 0.0f), glm::vec2(0.8f, 0.8f), 45.0f, glm::vec4(0.8f, 0.2f, 0.3f, 1.0f));
		Dooda::Renderer2D::DrawQuad(glm::vec2(0.5f, -0.5f), glm::vec2(0.5f, 0.75f), glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));
		Dooda::Renderer2D::DrawQuad(glm::vec3(0.0f, 0.0f, -0.1f), glm::vec2(10.0f, 10.0f), "CheckerBoard", 10.0f, glm::vec4(1.0f, 0.8f, 0.8f, 1.0f));
		Dooda::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	DD_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor)); 
	ImGui::End();
}

void Sandbox2D::OnEvent(Dooda::Event& e)
{
	DD_PROFILE_FUNCTION();

	m_CameraController.OnEvent(e);
}