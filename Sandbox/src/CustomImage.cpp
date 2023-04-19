#include "CustomImage.h"

CustomImage::CustomImage()
	: Array3D(100, 100, 4)
{
}

CustomImage::CustomImage(int x, int y)
	: Array3D(x, y, 4)
{

}

CustomImage::CustomImage(int x, int y, int colour[4])
	: Array3D(x, y, 4)
{
	SetUniformArray(colour);
}

CustomImage::~CustomImage()
{
}
