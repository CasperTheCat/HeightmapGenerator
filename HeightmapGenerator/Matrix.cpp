// Heightmap Matrix

#include "Core.h"

namespace Heightmap
{
	//////////////////////////////////////////////////
	// Initialise the Matrix
	//
	void Map::initialise(uint16_t MatrixSize)
	{
		if (this->bIsInit) return;

		/// Create square matrix of MatrixSize
		this->matrixPointer = new float[MatrixSize * MatrixSize];

		/// Finished, Initialisation Complete
		this->bIsInit = true;
		this->matrixSize = MatrixSize;
	}

	//////////////////////////////////////////////////
	// Default Constructor
	//
	Map::Map()
	{
		/// Blank Initialise
		this->matrixPointer = nullptr;
		this->matrixSize = 0;
	}

	//////////////////////////////////////////////////
	// Initialising Constructor
	Map::Map(uint16_t MatrixSize)
	{
		/// Construct a matrix
		initialise(MatrixSize);
	}

	//////////////////////////////////////////////////
	// Deconstructor
	//
	Map::~Map()
	{
		/// Unallocate the memory
		if (!this->bIsInit && this->matrixPointer == nullptr) return;

		/// Delete the matrix
		delete this->matrixPointer;
	}

	//////////////////////////////////////////////////
	// Map - Generate with Control Points
	//
	void Map::mapCPGenerate(uint16_t controlPoints)
	{
		/// Make random height
		/*std::default_random_engine gen_engine;
		std::binomial_distribution<float> distribution(0, 255);
		auto hRand = std::bind(distribution, gen_engine);*/
	}

	//////////////////////////////////////////////////
	// Generate the Heightmap
	//
	void Map::generateHeightmap(uint32_t seed)
	{
		if (!this->bIsInit) return;

		/// Create Perlin noise
		Noise *nGen = new Perlin(seed);

		/// Generate map from noise
		for (int y = 0; y < this->matrixSize; y++)
		{
			for (int x = 0; x < this->matrixSize; x++)
			{
				auto cy = double(y) / double(this->matrixSize);
				auto cx = double(x) / double(this->matrixSize);

				this->matrixPointer[y * matrixSize + x] = nGen->generateNoise(10 * cx,10 * cy, 0.8);
			}
		}

		delete nGen;
	}

	//////////////////////////////////////////////////
	// Accessor Methods
	//
	float* Map::getArray() const
	{
		return this->bIsInit ? this->matrixPointer : nullptr;
	}

}
