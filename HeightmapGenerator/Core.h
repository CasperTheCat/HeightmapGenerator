#pragma once

// Heightmap Generator for Windows UE4

// DLL Import Export

#ifdef HGCOREEXPORT
#define HGCOREAPI __declspec(dllexport)
#else
#define HGCOREAPI __declspec(dllimport)
#endif

#include <cstdint>

namespace Heightmap
{
	// Heightmap Matrix
	class HGCOREAPI Matrix
	{
		float **matrixPointer;
		uint16_t matrixSize;
		bool bIsInit = false;
	public:
		// Default Constructor
		Matrix();

		void initialise(uint16_t MatrixSize);

		// Size Spec Constructor
		Matrix(uint16_t MatrixSize);

		// Default Deconstuctor
		~Matrix();

	protected:
		
	};
}