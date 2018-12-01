#include "Core.h"
#include <algorithm>
#include <numeric>

namespace Heightmap
{
	//* https://github.com/sol-prog/Perlin_Noise/blob/master/PerlinNoise.cpp *//

	//////////////////////////////////////////////////
	// Perlin Default Constructor
	//
	Perlin::Perlin()
	{
		this->vecParam = {
				151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
				8,99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
			35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,
			134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
			55,46,245,40,244,102,143,54, 65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
			18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,
			250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
			189,28,42,223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167,
			43,172,9,129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,
			97,228,251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,
			107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
			138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 };

		this->vecParam.insert(this->vecParam.end(), this->vecParam.begin(), this->vecParam.end());
	}


	//////////////////////////////////////////////////
	// Perlin Constructor
	//
	Perlin::Perlin(uint32_t seed)
	{
		/// Resize the vector
		this->vecParam.resize(256);

		/// Initial with values from 0 to 255
		iota(this->vecParam.begin(), this->vecParam.end(), 0);

		/// Create Random generator
		//std::default_random_engine rGen(seed);
		std::mt19937_64 rGen(seed);

		/// Shuffle vector using rGen engine
		shuffle(this->vecParam.begin(), this->vecParam.end(), rGen);

		/// Dup Vector
		this->vecParam.insert(this->vecParam.end(),this->vecParam.begin(), this->vecParam.end());
	}

	Perlin::Perlin(std::mt19937_64 &rng)
	{
		/// Resize the vector
		this->vecParam.resize(256);

		/// Initial with values from 0 to 255
		iota(this->vecParam.begin(), this->vecParam.end(), 0);

		/// Create Random generator
		//std::default_random_engine rGen(seed);
		//std::mt19937_64 rGen(seed);

		printf("%llu\n", rng());

		/// Shuffle vector using rGen engine
		shuffle(this->vecParam.begin(), this->vecParam.end(), rng);

		/// Dup Vector
		this->vecParam.insert(this->vecParam.end(),this->vecParam.begin(), this->vecParam.end());
	}

	//////////////////////////////////////////////////
	// Linear Interpolate
	//
	double Perlin::lerp(double v0, double v1, double t)
	{
		return (1 - t) * v0 + t * v1;
		//return v0 + t * (v1 - v0);
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
	double Perlin::gradient(int grad, double x, double y, double z)
	{
		int gLow = grad & 15;

		double u = gLow < 8 ? x : y;
		double v = gLow < 4 ? y : gLow == 12 || gLow == 14 ? x : z;

		return ((gLow & 1) == 0 ? u : -u) + ((gLow & 2) == 0 ? v : -v);
	}


	//////////////////////////////////////////////////
	// Generate Noise
	//
	double Perlin::generateNoise(double xCoord, double yCoord, double zCoord)
	{
		auto ixCoord = int(floor(xCoord)) & 0xFF;
		auto iyCoord = int(floor(yCoord)) & 0xFF;
		auto izCoord = int(floor(zCoord)) & 0xFF;

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

		double res = lerp(
			lerp(
				lerp(
					gradient(this->vecParam[pAa], xCoord, yCoord, zCoord),
					gradient(this->vecParam[pBa], xCoord - 1, yCoord, zCoord),
					x),
				lerp(
					gradient(this->vecParam[pAb], xCoord, yCoord - 1, zCoord),
					gradient(this->vecParam[pBb], xCoord - 1, yCoord - 1, zCoord),
					x),
				y),
			lerp(
				lerp(
					gradient(this->vecParam[pAa + 1], xCoord, yCoord, zCoord - 1),
					gradient(this->vecParam[pBa + 1], xCoord - 1, yCoord, zCoord - 1),
					x),
				lerp(
					gradient(this->vecParam[pAb + 1], xCoord, yCoord - 1, zCoord - 1),
					gradient(this->vecParam[pBb + 1], xCoord - 1, yCoord - 1, zCoord - 1),
					x),
				y),
			z);
		return (res + 1.0) / 2.0;
	}


	//////////////////////////////////////////////////
	// Perlin Deconstructor
	//
	Perlin::~Perlin()
	{
		
	}


}