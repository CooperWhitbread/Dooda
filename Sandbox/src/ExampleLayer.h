#pragma once

#include <Dooda.h>

class ExampleLayer : public Dooda::Layer
{
public:
	ExampleLayer();

	void OnUpdate(Dooda::Timestep ts) override;

	void OnImGuiRender() override;

	void OnEvent(Dooda::Event& e) override;

private: //Variables
	Dooda::ShaderLibrary m_ShaderLibrary;
	Dooda::Ref<Dooda::Shader> m_Shader;
	Dooda::Ref<Dooda::VertexArray> d_vertexArray;

	Dooda::Ref<Dooda::Shader> m_FlatColorShader;
	Dooda::Ref<Dooda::VertexArray> m_SquareVA;

	Dooda::Ref<Dooda::Texture2D> m_Texture, m_ChernoLogoTexture;

	Dooda::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = glm::vec3(0.2f, 0.3f, 0.8f);

};
