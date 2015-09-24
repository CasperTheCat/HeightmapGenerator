#include "HGEntry.h"
#include "../HeightmapGenerator/Core.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "FreeImage.h"

//////////////////////////////////////////////////
// BMP Write
//
void fWrite(float *t_p, uint16_t sizeXY)
{
	FreeImage_Initialise();

	auto iPtr = FreeImage_Allocate(sizeXY, sizeXY, 24);

	RGBQUAD color;

	for (int i = 0; i < sizeXY; i++)
	{
		for (int y = 0; y < sizeXY; y++)
		{
			auto n = t_p[i * sizeXY + y];
			if(n < 0.35)
			{
				color.rgbRed = 0;
				color.rgbGreen = 127;
				color.rgbBlue = 255;
				FreeImage_SetPixelColor(iPtr, i, y, &color);
			} 
			else if (n >= 0.35 && n < 0.6)
			{
				color.rgbRed = 30;
				color.rgbGreen = 100;
				color.rgbBlue = 30;
				FreeImage_SetPixelColor(iPtr, i, y, &color);
			} 
			else if (n >= 0.6 && n < 0.825)
			{
				color.rgbRed = 150;
				color.rgbGreen = 150;
				color.rgbBlue = 150;
				FreeImage_SetPixelColor(iPtr, i, y, &color);
			}
			else
			{
				color.rgbRed = 255;
				color.rgbGreen = 255;
				color.rgbBlue = 255;
				FreeImage_SetPixelColor(iPtr, i, y, &color);
			}


		}
	}

	FreeImage_Save(FIF_PNG,iPtr,"TST.png",0);

	FreeImage_Unload(iPtr);

	FreeImage_DeInitialise();


}

//////////////////////////////////////////////////
// Entry Point
//
int main(int argc, char** argv)
{
	auto tMat = new Heightmap::Map(4096);
	tMat->generateHeightmap(5555);
	float *tMArray = tMat->getArray();

	fWrite(tMArray, 4096);

	delete tMat;
	return 0;
}
