#include "CustomImage.h"
#include <iostream>
#include <chrono>

CustomImage::CustomImage()
	: Array3D(100, 100, 4)
{
	m_Seed = std::chrono::system_clock::now().time_since_epoch().count();
}

CustomImage::CustomImage(int x, int y)
	: Array3D(x, y, 4)
{
	m_Seed = std::chrono::system_clock::now().time_since_epoch().count();
}

CustomImage::CustomImage(int x, int y, int colour[4])
	: Array3D(x, y, 4)
{
	m_Seed = std::chrono::system_clock::now().time_since_epoch().count();
	SetUniformArray(colour);
}

CustomImage::~CustomImage()
{
}

void CustomImage::GenerateRandomNoise(int seed)
{
	int value = seed;

	for (int x = 0; x < m_X; x++)
	{
		for (int y = 0; y < m_Y; y++)
		{
			value = GenerateRandomNumber(value);
			int colour[] = { value, value, value, 255 };
			SetIndexed(x, y, colour);
		}
	}
}

int CustomImage::GenerateRandomNumber(int seed)
{
	if (seed == 0)
		seed = m_Seed;

	seed ^= seed << 13;
	seed = seed % 2147483647;
	seed ^= seed >> 7;
	seed ^= seed << 5;

	m_Seed = seed;
	return seed;
}
