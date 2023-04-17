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
	m_ImageTexture2 = Dooda::Texture2D::Create(m_ImageSize, m_ImageSize);
	//m_ImageTexture = Dooda::Texture2D::Create("assets/textures/Checkerboard.png");

	GenerateRandomNoise();
	m_ImageTexture->SetData(m_Image, m_ImageSize * m_ImageSize * 4);
	m_ImageTexture2->SetData(m_Image2, m_ImageSize * m_ImageSize * 4);
	

}

void TestingLayer::OnDetach()
{
	DD_PROFILE_FUNCTION();
}

void TestingLayer::OnUpdate(Dooda::Timestep ts)
{
	DD_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);

	// Render
	Dooda::Renderer2D::ResetStats();

	Dooda::RenderCommand::SetClearColor(glm::vec4{ 0.1f, 0.1f, 0.1f, 1 });
	Dooda::RenderCommand::Clear();

	// Rendering
	Dooda::Renderer2D::BeginScene(m_CameraController.GetCamera());

	GenerateRandomNoise();
	m_ImageTexture->SetData(m_Image, m_ImageSize * m_ImageSize * 4);
	Dooda::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 2.0f }, m_ImageTexture);
	Dooda::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.0f }, { 1.0f, 2.0f }, m_ImageTexture2);

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

void TestingLayer::GenerateRandomNoise()
{
	std::random_device rd;
	std::mt19937 gen(31532);
	std::uniform_int_distribution<> distr1(0, 255);
	Dooda::Timer timer;
	for (int x = 0; x < m_ImageSize; x++)
	{
		for (int y = 0; y < m_ImageSize; y++)
		{
			// Built in (0.04-0.05)
			//int value = std::rand() % 256;

			// Built in 2 (0.09-0.01)
			int value2 = distr1(gen);
			
			//Custom 1 (0.01-0.02)
			//int value = (x * 173151123 + y * 87698762342 + 88769876234) % 255;

			//Custom 2 (0.2-0.3)
			//int value = (x * 173151123 + y * 87698762342 + 88769876234 + x*y*10987098234) % 255;

			// Custom 3 (0.01-0.02)
			/*int value = (x * y - x - y * y * y * x + 878669);
			value ^= value << 1;
			value ^= value >> 3;
			value ^= value << 5;*/

			// Custom 3 (0.01-0.02)
			int value = (x ^ y * 3151975234 + y ^ y * 1351235 + y * x * 78690769 + 878669);
			value ^= value << 1 & 0x8374f73fU;
			value ^= value >> 3 & 0x87677f67U;
			value ^= value << 4 & 0x2f38f2f4U;
			
			m_Image[x][y][0] = value;
			m_Image[x][y][1] = value;
			m_Image[x][y][2] = value;
			m_Image[x][y][3] = 255;


			m_Image2[x][y][0] = value2;
			m_Image2[x][y][1] = value2;
			m_Image2[x][y][2] = value2;
			m_Image2[x][y][3] = 255;
		}
	}
	std::cout << timer.Elapsed() << std::endl;
}
