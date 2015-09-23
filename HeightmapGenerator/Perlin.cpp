#include "Core.h"
#include <numeric>

namespace Heightmap
{

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


	}


	//////////////////////////////////////////////////
	// Perlin Deconstructor
	//
	Perlin::~Perlin()
	{
		
	}


}