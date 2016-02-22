#include "HGEntry.h"
#include "../HeightmapGenerator/Core.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "FreeImage.h"
#include <opencv2\opencv.hpp>

//////////////////////////////////////////////////
// Define and Typedef
//
typedef unsigned short USHORT;


//////////////////////////////////////////////////
// Clamp
//
__forceinline float clamp(float val)
{
	return (val < 0.f) ? 0.f : ((val > 1.f) ? 1.0f : val);
}

//////////////////////////////////////////////////
// BMP Write
//
void fWrite(float *t_p, uint16_t sizeXY)
{

	///Create writable
	auto image = cvCreateImage(cvSize(sizeXY, sizeXY), 16, 1);
	
	/// Convert FP32 array to USHORT array
	auto heightShort = new USHORT[sizeXY * sizeXY];
	uint32_t index;

	for (index = 0; index < (sizeXY * sizeXY); index++)
		heightShort[index] = static_cast<USHORT>(0xffff * clamp(t_p[index]));
	
	/// Copy data to image
	memcpy_s(
				image->imageData,
				image->width * image->height * 2,
				heightShort,
				sizeXY * sizeXY * sizeof(USHORT)
			);

	cvSaveImage("Heightmap.png", image);




	//FreeImage_Initialise();

	//auto iPtr = FreeImage_Allocate(sizeXY, sizeXY, 48);

	//RGBQUAD color;

	//for (int i = 0; i < sizeXY; i++)
	//{
	//	for (int y = 0; y < sizeXY; y++)
	//	{
	//		color.rgbRed = uint16_t(0xffff * clamp(t_p[i * sizeXY + y]));
	//		color.rgbGreen = uint16_t(0xffff * clamp(t_p[i * sizeXY + y]));
	//		color.rgbBlue = uint16_t(0xffff * clamp(t_p[i * sizeXY + y]));

	//		/*auto n = t_p[i * sizeXY + y];
	//		if (n < 0.2)
	//		{
	//			color.rgbRed = 0;
	//			color.rgbGreen = 67;
	//			color.rgbBlue = 127;
	//		}
	//		else if (n >= 0.2 && n < 0.32)
	//		{
	//			color.rgbRed = 0;
	//			color.rgbGreen = 127;
	//			color.rgbBlue = 255;
	//		}
	//		else if (n >= 0.32 && n < 0.35)
	//		{
	//			color.rgbRed = 200;
	//			color.rgbGreen = 127;
	//			color.rgbBlue = 0;
	//		}
	//		else if (n >= 0.35 && n < 0.45)
	//		{
	//			color.rgbRed = 30;
	//			color.rgbGreen = 130;
	//			color.rgbBlue = 30;
	//		}
	//		else if (n >= 0.45 && n < 0.55)
	//		{
	//			color.rgbRed = 50;
	//			color.rgbGreen = 120;
	//			color.rgbBlue = 50;
	//		}
	//		else if (n >= 0.55 && n < 0.6)
	//		{
	//			color.rgbRed = 60;
	//			color.rgbGreen = 110;
	//			color.rgbBlue = 60;
	//		}
	//		else if (n >= 0.6 && n < 0.65)
	//		{
	//			color.rgbRed = 110;
	//			color.rgbGreen = 110;
	//			color.rgbBlue = 110;
	//		}
	//		else if (n >= 0.65 && n < 0.7)
	//		{
	//			color.rgbRed = 120;
	//			color.rgbGreen = 120;
	//			color.rgbBlue = 120;
	//		}
	//		else if (n >= 0.7 && n < 0.75)
	//		{
	//			color.rgbRed = 150;
	//			color.rgbGreen = 150;
	//			color.rgbBlue = 150;
	//		}
	//		else if (n >= 0.75 && n < 0.825)
	//		{
	//			color.rgbRed = 150;
	//			color.rgbGreen = 150;
	//			color.rgbBlue = 150;
	//		}
	//		else
	//		{
	//			color.rgbRed = 255;
	//			color.rgbGreen = 255;
	//			color.rgbBlue = 255;
	//		}*/
	//		FreeImage_SetPixelColor(iPtr, i, y, &color);

	//		/// Limit only 8 greys
	//		/*auto n = round(7 * t_p[i * sizeXY + y]) / 7;
	//		color.rgbRed = uint8_t(255 * n);
	//		color.rgbGreen = uint8_t(255 * n);
	//		color.rgbBlue = uint8_t(255 * n);
	//		FreeImage_SetPixelColor(iPtr, i, y, &color);*/
	//	}
	//}

	//FreeImage_Save(FIF_PNG, iPtr, "Heightmap.tif", 0);

	//FreeImage_Unload(iPtr);

	//FreeImage_DeInitialise();


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
