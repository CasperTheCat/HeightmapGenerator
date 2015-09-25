#include "HGEntry.h"
#include "../HeightmapGenerator/Core.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "FreeImage.h"

//////////////////////////////////////////////////
// Linear Interpolate
//


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
			/*color.rgbRed = uint8_t(255 * t_p[i * sizeXY + y]);
			color.rgbGreen = uint8_t(255 * t_p[i * sizeXY + y]);
			color.rgbBlue = uint8_t(255 * t_p[i * sizeXY + y]);
			FreeImage_SetPixelColor(iPtr, i, y, &color);*/
			auto n = t_p[i * sizeXY + y];
			if (n < 0.2)
			{
				color.rgbRed = 0;
				color.rgbGreen = 67;
				color.rgbBlue = 127;
			}
			else if (n >= 0.2 && n < 0.32)
			{
				color.rgbRed = 0;
				color.rgbGreen = 127;
				color.rgbBlue = 255;
			}
			else if (n >= 0.32 && n < 0.35)
			{
				color.rgbRed = 200;
				color.rgbGreen = 127;
				color.rgbBlue = 0;
			}
			else if (n >= 0.35 && n < 0.6)
			{
				color.rgbRed = 30;
				color.rgbGreen = 100;
				color.rgbBlue = 30;
			}
			else if (n >= 0.6 && n < 0.825)
			{
				color.rgbRed = 150;
				color.rgbGreen = 150;
				color.rgbBlue = 150;
			}
			else
			{
				color.rgbRed = 255;
				color.rgbGreen = 255;
				color.rgbBlue = 255;
			}
			FreeImage_SetPixelColor(iPtr, i, y, &color);

			/// Limit only 8 greys
			/*auto n = round(7 * t_p[i * sizeXY + y]) / 7;
			color.rgbRed = uint8_t(255 * n);
			color.rgbGreen = uint8_t(255 * n);
			color.rgbBlue = uint8_t(255 * n);
			FreeImage_SetPixelColor(iPtr, i, y, &color);*/
		}
	}

	FreeImage_Save(FIF_PNG, iPtr, "TST.png", 0);

	FreeImage_Unload(iPtr);

	FreeImage_DeInitialise();


}

//////////////////////////////////////////////////
// Entry Point
//
int main(int argc, char** argv)
{
	uint16_t mSize = atoi(argv[1]);
	uint32_t seed = atoi(argv[2]);
	uint32_t noiseMul = atoi(argv[3]);

	auto tMat = new Heightmap::Map(mSize);
	tMat->generateHeightmap(seed, noiseMul);
	float *tMArray = tMat->getArray();

	fWrite(tMArray, mSize);

	delete tMat;
	return 0;
}
