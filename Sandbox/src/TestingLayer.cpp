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
	m_ImageC = Dooda::CreateRef<CustomImage, int, int>(1000, 1000);
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

	// Image generation
	//GenerateRandomNoise();
	int colour[] = { 255, 255, 100, 255 };
	m_ImageC->SetUniformArray(colour);
	m_ImageTexture->SetData(m_ImageC->GetData(), m_ImageC->GetDataSize());

	colour[2] = 0;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 400; j < 600; j++)
		{
			m_ImageC->SetIndexed(i, j, colour);
		}
	}

	m_ImageTexture2->SetData(m_ImageC->GetData(), m_ImageC->GetDataSize());


	// Render
	Dooda::Renderer2D::ResetStats();

	Dooda::RenderCommand::SetClearColor(glm::vec4{ 0.1f, 0.1f, 0.1f, 1 });
	Dooda::RenderCommand::Clear();

	// Rendering
	Dooda::Renderer2D::BeginScene(m_CameraController.GetCamera());

	//Drawing images
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
	/*unsigned char image[1000][1000][4];

	Dooda::Timer timer;
	for (int x = 0; x < m_ImageSize; x++)
	{
		for (int y = 0; y < m_ImageSize; y++)
		{
			int value = (x ^ y * 3151975234 + y ^ y * 1351235 + y * x * 78690769 + 878669);
			value ^= value << 1 & 0x8374f73fU;
			value ^= value >> 3 & 0x87677f67U;
			value ^= value << 4 & 0x2f38f2f4U;
			
			m_Image[x][y][0] = value;
			m_Image[x][y][1] = value;
			m_Image[x][y][2] = value;
			m_Image[x][y][3] = 255;
		}
	}
	std::cout << timer.Elapsed() << std::endl;*/
}


int TestingLayer::RandomNumberGenerator(int seed)
{
	return 0;
}
