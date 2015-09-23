#include "Core.h"
#include <numeric>
#include <algorithm>

namespace Heightmap
{
	//* https://github.com/sol-prog/Perlin_Noise/blob/master/PerlinNoise.cpp *//

	//////////////////////////////////////////////////
	// Perlin Constructor
	//
	Perlin::Perlin(uint32_t seed)
	{
		/// Resize the vector
		this->vecParam.resize(256);

		/// Initial with values from 0 to 255
		std::iota(this->vecParam.begin(), this->vecParam.end(), 0);

		/// Create Random generator
		std::default_random_engine rGen(seed);

		/// Shuffle vector using rGen engine
		std::shuffle(this->vecParam.begin(), this->vecParam.end(),rGen);

		/// Dup Vector
		this->vecParam.insert(this->vecParam.end(),this->vecParam.begin(), this->vecParam.end());
	}

	//////////////////////////////////////////////////
	// Generate Noise
	//
	double Perlin::generateNoise(double xCoord, double yCoord, double zCoord)
	{
		uint8_t ixCoord = static_cast<int>(floor(xCoord)) & 255;
		uint8_t iyCoord = static_cast<int>(floor(yCoord)) & 255;
		uint8_t izCoord = static_cast<int>(floor(zCoord)) & 255;

		xCoord -= floor(xCoord);
		yCoord -= floor(yCoord);
		zCoord -= floor(zCoord);

		auto x = fade(xCoord);
		auto y = fade(yCoord);
		auto z = fade(zCoord);

		auto pA = this->vecParam[ixCoord] + iyCoord;
		auto pAa = this->vecParam[pA] + izCoord;
		auto pAb = this->vecParam[pA + 1] + izCoord;

		auto pB = this->vecParam[ixCoord + 1] + iyCoord;
		auto pBa = this->vecParam[pB] + izCoord;
		auto pBb = this->vecParam[pB + 1] + izCoord;

		return 0;
	}


	//////////////////////////////////////////////////
	// Perlin Deconstructor
	//
	Perlin::~Perlin()
	{
		
	}


}