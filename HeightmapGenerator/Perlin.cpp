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
	// Linear Interpolate
	//
	double Perlin::lerp(double v0, double v1, double t)
	{
		return (1 - t) * v0 + t * v1;
	}

	//////////////////////////////////////////////////
	// Perlin Fade
	//
	double Perlin::fade(double in)
	{
		return in * in * in * (in * (in * 6 - 15) + 10);
	}

	//////////////////////////////////////////////////
	// Perlin Gradient
	//
	double Perlin::gradient(uint8_t grad, double x, double y, double z)
	{
		uint8_t gLow = grad & 15;

		double u = gLow < 8 ? x : y;
		double v = gLow < 4 ? y : gLow == 12 || gLow == 14 ? x : z;

		return ((gLow & 1) == 0 ? u : -u) + ((gLow & 2) == 0 ? v : -v);
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

		double res = lerp(z,
			lerp(y,
				lerp(x,
					gradient(this->vecParam[pAa], x, y, z),
					gradient(this->vecParam[pBa], x - 1, y, z)),
				lerp(x,
					gradient(this->vecParam[pAb], x, y - 1, z),
					gradient(this->vecParam[pBb], x - 1, y - 1, z))),
			lerp(y,
				lerp(x,
					gradient(this->vecParam[pAa + 1], x, y, z - 1),
					gradient(this->vecParam[pBa + 1], x - 1, y, z - 1)),
				lerp(x,
					gradient(this->vecParam[pAb + 1], x, y - 1, z - 1),
					gradient(this->vecParam[pBb + 1], x - 1, y - 1, z - 1))));
		return (res + 1.0) / 2.0;
	}


	//////////////////////////////////////////////////
	// Perlin Deconstructor
	//
	Perlin::~Perlin()
	{
		
	}


}