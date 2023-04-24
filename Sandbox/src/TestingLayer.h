#pragma once
#include <Dooda.h>

#include "CustomImage.h"

class TestingLayer : public Dooda::Layer
{
public:
	TestingLayer();
	virtual ~TestingLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Dooda::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Dooda::Event& e) override;

private: //Variables
	Dooda::OrthographicCameraController m_CameraController;

	Dooda::Ref<Dooda::Texture2D> m_ImageTexture;
	glm::vec4 m_Colour = glm::vec4(1.0, 0.1, 1.0, 1.0);
	int m_ImageSize = 100;
	Dooda::Ref<CustomImage> m_ImageC;
};

