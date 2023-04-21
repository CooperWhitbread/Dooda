#pragma once
#include "Array3D.h"

class CustomImage : public Array3D
{
public:
	CustomImage();
	CustomImage(int x, int y);
	CustomImage(int x, int y, int colour[4]);

	~CustomImage();

	void GenerateRandomNoise(int seed = 0); // If left blank, a random seed will be used

	int GenerateRandomNumber(int seed = 0); // If left blank, a random see will be used

private:
	int m_Seed = 0;

};

