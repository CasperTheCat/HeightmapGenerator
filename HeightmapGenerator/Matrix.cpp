// Heightmap Matrix

#include "Core.h"

namespace Heightmap
{
	//////////////////////////////////////////////////
	// Initialise the Matrix
	//
	void Matrix::initialise(uint16_t MatrixSize)
	{
		if (this->bIsInit) return;

		/// Initialise the First Tier
		this->matrixPointer = new float*[MatrixSize];

		/// Initialise the Second Tier
		for (uint16_t i = 0; i < MatrixSize;i++)
		{
			this->matrixPointer[i] = new float[MatrixSize];
		}

		/// Finished, Initialisation Complete
		this->bIsInit = true;
		this->matrixSize = MatrixSize;
	}
	
	//////////////////////////////////////////////////
	// Default Constructor
	//
	Matrix::Matrix()
	{
		/// Do nothing
	}

	//////////////////////////////////////////////////
	// Initialising Constructor
	Matrix::Matrix(uint16_t MatrixSize)
	{
		/// Construct a matrix
		initialise(MatrixSize);
	}

	//////////////////////////////////////////////////
	// Deconstructor
	//
	Matrix::~Matrix()
	{
		/// Unallocate the memory
		if (!this->bIsInit) return;

		for (uint16_t i = 0; i < this->matrixSize; i++)
		{
			delete this->matrixPointer[i];
		}

		delete matrixPointer;
	}
}
