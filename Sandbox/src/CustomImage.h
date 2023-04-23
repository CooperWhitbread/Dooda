#pragma once
#include "Array3D.h"

class CustomImage : public Array3D
{
public:
	CustomImage();
	CustomImage(int x, int y, int depth = 4);
	CustomImage(int x, int y, int colour[], int depth = 4);

	~CustomImage();

	unsigned char* GetDataForVisual(); // Memory needs to be deleted
	int GetVisualDataSize() { return m_X * m_Y * 4; }

	void GenerateRandomNoise(int seed = 0); // If left blank, a random seed will be used

	int GenerateRandomNumber(int seed = 0); // If left blank, a random see will be used

private:
	int m_Seed = 0;

};

