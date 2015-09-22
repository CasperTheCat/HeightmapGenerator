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
	class HGCOREAPI Generic
	{
	public:
		static inline int iMod(int quo, int div);
	};

	// Heightmap Matrix
	class HGCOREAPI Matrix
	{
	private:
		// Matrix Array Pointer
		float *matrixPointer;

		// Size of the square matrix
		uint16_t matrixSize;

		// Bool for initialisation
		bool bIsInit = false;

		// Private Game of Life function
		void gameOfLife(uint8_t tHold);

		// Private game of Life check function
		uint8_t gameOfLifeNeighbours(uint32_t elem, uint32_t tElem);


	public:
		// Default Constructor
		Matrix();

		// Size Spec Constructor
		Matrix(uint16_t MatrixSize);

		// Default Deconstuctor
		~Matrix();

		// Initialise the Matrix
		void initialise(uint16_t MatrixSize);

		// Run Generation
		void generateHeightmap(uint8_t tHold);
		// Accesser Methods
		float *getArray() const;

	protected:
		
	};
}