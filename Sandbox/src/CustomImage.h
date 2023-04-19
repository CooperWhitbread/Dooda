#pragma once
#include "Array3D.h"

class CustomImage : public Array3D
{
public:
	CustomImage();
	CustomImage(int x, int y);
	CustomImage(int x, int y, int colour[4]);

	~CustomImage();

};

