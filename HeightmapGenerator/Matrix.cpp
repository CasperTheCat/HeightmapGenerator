// Heightmap Matrix

#include "Core.h"

namespace Heightmap
{
	inline double fullContrast(double n, double pivot, double contrastRatio)
	{
		return ((n - pivot) * contrastRatio) + pivot;
	}

	inline double fullContrastAndNormalise(double n, double pivot, double contrastRatio)
	{
		return (((n - pivot) * contrastRatio) + pivot) / (pivot * contrastRatio);
	}

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
	void Map::generateHeightmap(uint32_t seed, uint32_t _noiseMul)
	{
		if (!this->bIsInit) return;

		std::mt19937_64 twister(seed);
		auto noiseMul = _noiseMul * 0.001f;

		/// Create Perlin noise
		Noise *nGen = new Perlin(twister); // Base Gen
		Noise *rGen = new Perlin(twister);// + seed); // RoughnessGen
		Noise *fGen = new Perlin(twister);// + seed + seed); // Fine Gen
		Noise *cGen = new Perlin(twister);// + seed + seed); // Fine Gen
		Noise *mGen = new Perlin(twister);// + seed + seed); // Fine Gen
		Noise *mhGen = new Perlin(twister);// + seed + seed); // Fine Gen
		Noise *mmGen = new Perlin(twister);// + seed + seed); // Fine Gen


		double cy, cx;
		int x;

		double highestPoint = 0.f;
		double lowestPoint = 9090.f;

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
				//this->matrixPointer[y * matrixSize + x] =
				//	0.5 + nContrast(nGen->generateNoise(noiseMul * cx, noiseMul * cy, 0), 0.5, 1.0)
				//	+ nContrast(rGen->generateNoise(noiseMul * 2 * cx, noiseMul * 2 * cy, 0), 0.25, 0.25)
				//	+ nContrast(fGen->generateNoise(noiseMul * 1.5 * cx, noiseMul * 1.5 * cy, 0), 0.75, 0.125);

				/*this->matrixPointer[y * matrixSize + x] =
						nGen->generateNoise(noiseMul * cx, noiseMul * cy, 0) * 0.5f
						+
						rGen->generateNoise(noiseMul * 20 * cx, noiseMul * 20 * cy, 0) * 0.5f;
					//0.5 + nContrast(
					//	fGen->generateNoise(
					//		noiseMul * cx, noiseMul * cy, 0
					//	),
					//	0.5, 1.0
					//);*/
			
				auto nGenTap = nGen->generateNoise(noiseMul * 0.005 * cx, noiseMul * 0.005 * cy, 0);// * 2 - 1.0;
				auto mmGenTap = mmGen->generateNoise(noiseMul * 0.0002 * cx, noiseMul * 0.0002 * cy, 0);// * 2 - 1.0;

				auto rGenTap = rGen->generateNoise(noiseMul * 0.025 * cx, noiseMul * 0.025 * cy, 0);
				auto mhGenTap = mhGen->generateNoise(noiseMul * 0.001 * cx, noiseMul * 0.001 * cy, 0);

				auto cGenTap = cGen->generateNoise(noiseMul * 0.0010 * cx, noiseMul * 0.0010 * cy, 0);
				auto mGenTap = mGen->generateNoise(noiseMul * 0.0001 * cx, noiseMul * 0.0001 * cy, 0);
				
				auto fGenTap = fGen->generateNoise(noiseMul * 32 * cx, noiseMul * 32 * cy, 0);

				// Increase Slope
				//nGenTap = fullContrastAndNormalise(nGenTap, 0.5, 1);

				auto land = (mGenTap * 2 - 1) * cGenTap;

				land = land > -0.05 ? land : -0.05;
				auto mountains = nGenTap * (nGenTap * 1.1);//std::sin(nGenTap * 3.14);
				mountains = fullContrastAndNormalise(mountains, 0.75, 2);
				mountains = mountains * (mmGenTap  *2 - 1);
				mountains = mountains > 0 ? mountains : 0;

				auto hills = rGenTap * (mhGenTap * 2 - 1);//fullContrastAndNormalise(rGenTap, 0.5, 10);
				hills = hills > 0 ? hills : 0;
				auto noiseMixer = fGenTap;


				auto pointHeight =
					land * 10000 // height in metres
					+
					mountains * 500
					+ 
					hills * 20
					+ 
					noiseMixer * 0.2
				;

				//pointHeight = land;



				if(pointHeight > highestPoint) {highestPoint = pointHeight;}
				if(pointHeight < lowestPoint) {lowestPoint = pointHeight;}
				this->matrixPointer[y * matrixSize + x] = pointHeight;
			}
		}

		delete nGen;
		delete rGen;
		delete fGen;
		printf("HP: %lf\n", highestPoint);
		printf("LP %lf\n", lowestPoint);

		double oneOverHighest = 1 / (highestPoint - lowestPoint);

#pragma omp parallel for
		for (uint64_t y = 0; y < this->matrixSize * this->matrixSize; y++)
		{
			this->matrixPointer[y] = (this->matrixPointer[y] - lowestPoint) * oneOverHighest;
			//this->matrixPointer[y] = (this->matrixPointer[y] + 500) / 10000;
			//this->matrixPointer[y] += 0.5;
		}
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
