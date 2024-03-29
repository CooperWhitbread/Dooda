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

	m_CheckerboardTexture = Dooda::Texture2D::Create("assets/textures/Checkerboard.png");
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
	Dooda::Renderer2D::ResetStats();
	{
		DD_PROFILE_SCOPE("Renderer Prep");
		Dooda::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Dooda::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		DD_PROFILE_SCOPE("Renderer Draw");
		Dooda::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Dooda::Renderer2D::DrawRotatedQuad(glm::vec2(1.0f, 0.0f), glm::vec2(0.8f, 0.8f), 45.0f, m_SquareColor);
		Dooda::Renderer2D::DrawQuad(glm::vec2( -1.0f, 0.0f ), glm::vec2( 0.8f, 0.8f ), glm::vec4( 0.8f, 0.2f, 0.3f, 1.0f ));
		Dooda::Renderer2D::DrawQuad(glm::vec2(0.5f, -0.5f), glm::vec2(0.5f, 0.75f), glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));
		Dooda::Renderer2D::DrawQuad(glm::vec3(0.0f, 0.0f, -0.1f), glm::vec2(10.0f, 10.0f), m_CheckerboardTexture, 10.0f);
		Dooda::Renderer2D::DrawRotatedQuad(glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), rotation, m_CheckerboardTexture, 20.0f);
		Dooda::Renderer2D::EndScene();

		Dooda::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = glm::vec4( (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f );
				Dooda::Renderer2D::DrawQuad(glm::vec2( x, y ), glm::vec2( 0.45f, 0.45f ), color);
			}
		}
		Dooda::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	DD_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Dooda::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::SetWindowFontScale(2.8f);
	ImGui::End();
}

void Sandbox2D::OnEvent(Dooda::Event& e)
{
	DD_PROFILE_FUNCTION();

	m_CameraController.OnEvent(e);
}