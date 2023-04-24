#include "TestingLayer.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Dooda/Math/Math.h>
#include <Dooda/Core/Timer.h>
#include <Dooda/Utilities/PlatformUtilities.h>

#include <ImGuizmo.h>
#include <random>

TestingLayer::TestingLayer()
	: Layer("Testing"), m_CameraController(1280.0f / 720.0f)
{
}

void TestingLayer::OnAttach()
{
	DD_PROFILE_FUNCTION();

	m_ImageTexture = Dooda::Texture2D::Create(m_ImageSize, m_ImageSize);
	m_ImageC = Dooda::CreateRef<CustomImage>(m_ImageSize, m_ImageSize, 1);
	
	// Image generation
	m_ImageC->GenerateRandomNoise();
	auto data = m_ImageC->GetDataForVisual();
	m_ImageTexture->SetData(data, m_ImageC->GetVisualDataSize());
	delete[] data;
}

void TestingLayer::OnDetach()
{
	DD_PROFILE_FUNCTION();
}

void TestingLayer::OnUpdate(Dooda::Timestep ts)
{
	DD_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);

	// Game Updates
	m_ImageC->GenerateRandomNoise();
	auto data = m_ImageC->GetDataForVisual();
	m_ImageTexture->SetData(data, m_ImageC->GetVisualDataSize());
	delete[] data;

	// Render
	Dooda::Renderer2D::ResetStats();

	Dooda::RenderCommand::SetClearColor(glm::vec4{ 0.1f, 0.1f, 0.1f, 1 });
	Dooda::RenderCommand::Clear();

	// Rendering
	Dooda::Renderer2D::BeginScene(m_CameraController.GetCamera());

	//Drawing images
	Dooda::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 2.0f }, m_ImageTexture);

	Dooda::Renderer2D::EndScene();
}

void TestingLayer::OnImGuiRender()
{
	DD_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Dooda::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_Colour));
	ImGui::End();
}

void TestingLayer::OnEvent(Dooda::Event& e)
{
	m_CameraController.OnEvent(e);
}
