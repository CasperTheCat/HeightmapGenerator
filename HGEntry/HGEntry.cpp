#include "HGEntry.h"
#include "../HeightmapGenerator/Core.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "FreeImage.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

//////////////////////////////////////////////////
// Define and Typedef
//
typedef unsigned short USHORT;

struct BGR8Pixel3
{
	char blue;
	char green;
	char red;
};


//////////////////////////////////////////////////
// Clamp
//
inline float clamp(float val)
{
	return (val < 0.f) ? 0.f : ((val > 1.f) ? 1.0f : val);
}

void fWrite(USHORT *t_p, uint16_t sizeXY)
{
	assert(sizeof(BGR8Pixel3) == 3); // Must be 3 bytes
	///Create writable
	auto image = cvCreateImage(cvSize(sizeXY, sizeXY), 16, 1);

	memcpy(
				image->imageData,
				t_p,
				sizeXY * sizeXY * sizeof(USHORT)
			);

	cvSaveImage("Heightmap.png", image);
	return;
}

//////////////////////////////////////////////////
// BMP Write
//
void fWrite(float *t_p, uint16_t sizeXY)
{
	assert(sizeof(BGR8Pixel3) == 3); // Must be 3 bytes
	///Create writable
	auto image = cvCreateImage(cvSize(sizeXY, sizeXY), 16, 1);
	
	/// Convert FP32 array to USHORT array
	auto heightShort = new USHORT[sizeXY * sizeXY];
	uint32_t index;

	for (index = 0; index < (sizeXY * sizeXY); index++)
		heightShort[index] = static_cast<USHORT>(0xffff * clamp(t_p[index]));
	
	/// Copy data to image
	memcpy(
				image->imageData,
				heightShort,
				sizeXY * sizeXY * sizeof(USHORT)
			);

	cvSaveImage("Heightmap.png", image);
return;
	/*auto imageColour = cvCreateImage(cvSize(sizeXY, sizeXY), 8, 3);
	auto heightColour = new BGR8Pixel3[sizeXY * sizeXY];

	for (int i = 0; i < sizeXY; i++)
	{
		for (int y = 0; y < sizeXY; y++)
		{
			BGR8Pixel3 colour;
			auto n = t_p[i * sizeXY + y] * 10000;
			//auto n = static_cast<char>(0xff * std::floor(clamp(t_p[i * sizeXY + y]) * 0.99999999999999999f ));
			if (n < 100)
			{
				colour.red = 0;
				colour.green = 67;
				colour.blue = 127;
			}
			else if (n < 500)
			{
				colour.red = 0;
				colour.green = 127;
				colour.blue = 255;
			}
			else if (n < 501)
			{
				colour.red = 200;
				colour.green = 127;
				colour.blue = 0;
			}
			else if (n < 550)
			{
				colour.red = 30;
				colour.green = 130;
				colour.blue = 30;
			}
			else if (n < 600)
			{
				colour.red = 50;
				colour.green = 120;
				colour.blue = 50;
			}
			else if (n < 800)
			{
				colour.red = 60;
				colour.green = 110;
				colour.blue = 60;
			}
			else if (n < 2000)
			{
				colour.red = 110;
				colour.green = 110;
				colour.blue = 110;
			}
			else if (n < 3000)
			{
				colour.red = 120;
				colour.green = 120;
				colour.blue = 120;
			}
			else if ( n < 4000)
			{
				colour.red = 150;
				colour.green = 150;
				colour.blue = 150;
			}
			else if (n < 5000)
			{
				colour.red = 150;
				colour.green = 150;
				colour.blue = 150;
			}
			else
			{
				colour.red = 255;
				colour.green = 255;
				colour.blue = 255;
			}

			heightColour[i * sizeXY + y] = colour;
		}
	}

	memcpy(
			imageColour->imageData,
			heightColour,
			sizeXY * sizeXY * sizeof(BGR8Pixel3)
		);

	cvSaveImage("HeightmapColour.png", imageColour);*/
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

	/// Convert FP32 array to USHORT array
	auto heightShort = new USHORT[mSize * mSize];
	uint32_t index;

	for (index = 0; index < (mSize * mSize); index++)
		heightShort[index] = static_cast<USHORT>(0xffff * clamp(tMArray[index]));
	
	/// Copy data to image
	delete tMat;

	fWrite(heightShort, mSize);

	delete tMat;
	return 0;
}
