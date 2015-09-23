#include "HGEntry.h"
#include "../HeightmapGenerator/Core.h"
#include <vector>
#include <iostream>

//////////////////////////////////////////////////
// Entry Point
//
int main(int argc, char** argv)
{
	auto tMat = new Heightmap::Map(20);
	tMat->generateHeightmap(10);
	float *tMArray = tMat->getArray();

	for (auto i = 0; i < 20; i++)
	{
		for (auto y = 0; y < 20; y++)
		{
			printf("%0.1f\t", tMArray[(i * 20) + y]);
		}
		printf("\n");
	}

	delete tMat;
	getchar();
	return 0;
}
