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
	void Map::generateHeightmap(uint32_t seed, uint32_t noiseMul)
	{
		if (!this->bIsInit) return;

		/// Create Perlin noise
		Noise *nGen = new Perlin(seed); // Base Gen
		Noise *rGen = new Perlin(seed + seed); // RoughnessGen
		Noise *fGen = new Perlin(seed + seed + seed); // Fine Gen

		double cy, cx;
		int x;

		/// Generate map from noise
#pragma omp parallel for private(cx,cy,x)
		for (int y = 0; y < this->matrixSize; y++)
		{
			cy = double(y) / double(this->matrixSize);

			for (x = 0; x < this->matrixSize; x++)
			{
				/// This needs recalced every loop!
				cx = double(x) / double(this->matrixSize);


				/// nContrast Works with Base N, Terrain Reduction Percentile, Effect Multiplier
				this->matrixPointer[y * matrixSize + x] = 0.5
					+ nContrast(nGen->generateNoise(noiseMul * cx, noiseMul * cy, 0), 0.75, 1.5)
					+ nContrast(rGen->generateNoise(noiseMul * 2 * cx, noiseMul * 2 * cy, 0), 0.25, 0.25)
					+ nContrast(fGen->generateNoise(noiseMul * 8 * cx, noiseMul * 8 * cy, 0), 0.75, 0.125);
			}
		}

		delete nGen;
		delete rGen;
		delete fGen;
	}

	//////////////////////////////////////////////////
	// Accessor Methods
	//
	float* Map::getArray() const
	{
		return this->bIsInit ? this->matrixPointer : nullptr;
	}

	//////////////////////////////////////////////////
	// nContrast for Noise Gen
	//
	inline double Map::nContrast(double n, double pivot, double contrastRatio)
	{
		return (n - pivot) * contrastRatio;
	}


}
