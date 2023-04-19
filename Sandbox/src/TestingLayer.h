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

private:
	void GenerateRandomNoise();
	int RandomNumberGenerator(int seed);

private: //Variables
	Dooda::OrthographicCameraController m_CameraController;

	Dooda::Ref<Dooda::Texture2D> m_ImageTexture;
	Dooda::Ref<Dooda::Texture2D> m_ImageTexture2;
	glm::vec4 m_Colour = glm::vec4(1.0, 0.1, 1.0, 1.0);
	int m_ImageSize = 1000;
	unsigned char m_Image[1000][1000][4];
	unsigned char m_Image2[1000][1000][4];
	Dooda::Ref<CustomImage> m_ImageC;
};

