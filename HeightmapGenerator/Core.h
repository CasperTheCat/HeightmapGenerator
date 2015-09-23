#pragma once

// Heightmap Generator for Windows UE4

// DLL Import Export

#ifdef HGCOREEXPORT
#define HGCOREAPI __declspec(dllexport)
#else
#define HGCOREAPI __declspec(dllimport)
#endif

#include <cstdint>
#include <random>
#include <functional>



namespace Heightmap
{
	//////////////////////////////////////////////////
	// Generic Static Helpers
	//
	class HGCOREAPI Generic
	{
	public:
		static inline int iMod(int quo, int div);
	};

	//////////////////////////////////////////////////
	// Noise Polymorph
	//
	class HGCOREAPI Noise
	{
	public:
		virtual ~Noise();
		virtual double generateNoise(double xCoord, double yCoord, double zCoord);
	};
	
	//////////////////////////////////////////////////
	// Perlin Noise Generator
	//
	class HGCOREAPI Perlin : public Noise
	{
	private:
		// Vector Parameter
		std::vector<int> vecParam;
		// Fade noise
		double fade(double in);

		// Linear interpolate
		double lerp(double val, double pX, double pY);

		// Gradient function
		double gradient(uint8_t grad, double x, double y, double z);

	protected:

	public:
		// Seed Based Constructor
		Perlin(uint32_t seed);

		// Default Deconstructor
		~Perlin();

		// Generate Noise
		double generateNoise(double xCoord, double yCoord, double zCoord);
	};


	//////////////////////////////////////////////////
	// Map Class
	//
	class HGCOREAPI Map
	{
	private:
		// Matrix Array Pointer
		float *matrixPointer;

		// Size of the square matrix
		uint16_t matrixSize;

		// Bool for initialisation
		bool bIsInit = false;

		// Smooth Map
		void mapSmooth();

		// Control Point Generate
		void mapCPGenerate(uint16_t controlPoints);

	protected:


	public:
		// Default Constructor
		Map();

		// Size Spec Constructor
		Map(uint16_t MatrixSize);

		// Default Deconstuctor
		~Map();

		// Initialise the Matrix
		void initialise(uint16_t MatrixSize);

		// Run Generation
		void generateHeightmap(uint8_t tHold);
		// Accesser Methods
		float *getArray() const;
	};
}