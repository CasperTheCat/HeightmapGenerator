#include "HGEntry.h"
#include "../HeightmapGenerator/Core.h"
#include <vector>

//////////////////////////////////////////////////
// Entry Point
//
int main(int argc, char** argv)
{
	auto tMat = new Heightmap::Matrix();
	tMat->initialise(600);
	delete tMat;
	getchar();
	return 0;
}
