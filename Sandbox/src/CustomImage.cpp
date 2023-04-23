#include "CustomImage.h"
#include <iostream>
#include <chrono>

#include <Dooda/Core/Timer.h>

CustomImage::CustomImage()
	: Array3D(100, 100, 4)
{
	m_Seed = std::chrono::system_clock::now().time_since_epoch().count();
}

CustomImage::CustomImage(int x, int y, int depth)
	: Array3D(x, y, depth)
{
	m_Seed = std::chrono::system_clock::now().time_since_epoch().count();
}

CustomImage::CustomImage(int x, int y, int colour[], int depth)
	: Array3D(x, y, depth)
{
	m_Seed = std::chrono::system_clock::now().time_since_epoch().count();
	SetUniformArray(colour);
}

CustomImage::~CustomImage()
{
}

unsigned char* CustomImage::GetDataForVisual()
{
	unsigned char* array = new unsigned char[GetVisualDataSize()];

	if (m_Z == 4)
	{
		for (int x = 0; x < m_X; x++)
		{
			for (int y = 0; y < m_Y; y++)
			{
				for (int z = 0; z < m_Z; z++)
				{
					array[GetIndex(x, y, z)] = m_Array[GetIndex(x, y, z)];
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < m_X; x++)
		{
			for (int y = 0; y < m_Y; y++)
			{
				for (int z = 0; z < 3; z++)
				{
					array[GetIndex(x, y, z, 4)] = m_Array[GetIndex(x, y, 0)];
				}
				array[GetIndex(x, y, 3, 4)] = 255;
			}
		}
	}

	return array;
}

void CustomImage::GenerateRandomNoise(int seed)
{
	int value = seed;
	int* colour = new int[m_Z];

	for (int x = 0; x < m_X; x++)
	{
		for (int y = 0; y < m_Y; y++)
		{
			value = GenerateRandomNumber(value);

			if (m_Z > 1)
			{
				for (int i = 0; i < m_Z - 1; i++)
					colour[i] = value;
				colour[m_Z - 1] = 255;
			}
			else
			{
				colour[0] = value;
			}

			SetIndexed(x, y, colour);
		}
	}

	delete[] colour;
}

int CustomImage::GenerateRandomNumber(int seed)
{
	if (seed == 0)
		seed = m_Seed;

	seed ^= seed << 13;
	seed = seed % 2147483647;
	seed ^= seed >> 7;
	seed ^= seed << 5;

	if (seed != 0)
		m_Seed = seed;
	else
		m_Seed = std::chrono::system_clock::now().time_since_epoch().count();

	return seed;
}
