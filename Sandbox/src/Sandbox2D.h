#pragma once

#include <Dooda.h>

class Sandbox2D : public Dooda::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Dooda::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Dooda::Event& e) override;
private:
	Dooda::OrthographicCameraController m_CameraController;

	Dooda::Ref<Dooda::VertexArray> m_SquareVA;
	Dooda::Ref<Dooda::Shader> m_FlatColorShader; 

	Dooda::Ref<Dooda::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = glm::vec4( 0.2f, 0.3f, 0.8f, 1.0f );
};