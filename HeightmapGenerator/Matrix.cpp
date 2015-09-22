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

		/// Create square matrix of MatrixSize
		this->matrixPointer = new float[MatrixSize * MatrixSize];

		/// Finished, Initialisation Complete
		this->bIsInit = true;
		this->matrixSize = MatrixSize;
	}
	
	//////////////////////////////////////////////////
	// Default Constructor
	//
	Matrix::Matrix()
	{
		/// Blank Initialise
		this->matrixPointer = nullptr;
		this->matrixSize = 0;
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
		if (!this->bIsInit && this->matrixPointer == nullptr) return;

		/// Delete the matrix
		delete matrixPointer;
	}

	//////////////////////////////////////////////////
	// Generate the Heightmap
	//
	void Matrix::generateHeightmap(uint8_t tHold)
	{
		for (int i = 0; i < this->matrixSize; i++)
		{
			this->matrixPointer[i*this->matrixSize + i] = float(tHold);
			this->matrixPointer[i*this->matrixSize] = float(tHold);
			this->matrixPointer[i*this->matrixSize - i] = float(tHold);
		}
		/// Conways Game of Life over 5 iterations
#pragma unroll (5)
		for (int i = 0; i < 5; i++)
		{
			/// Game of Life
			gameOfLife(tHold);
		}
	}

	//////////////////////////////////////////////////
	// Conways Game of Life: Check Neighbours
	//
	uint8_t Matrix::gameOfLifeNeighbours(uint32_t elem, uint32_t tElem)
	{
		auto n = 0;
		/// North
		if (this->matrixPointer[Generic::iMod(elem - this->matrixSize, tElem)] > 127.5f) n++;

		/// South
		if (this->matrixPointer[Generic::iMod(elem + this->matrixSize, tElem)] > 127.5f) n++;

		/// East
		if (this->matrixPointer[Generic::iMod(elem + 1, tElem)] > 127.5f) n++;

		/// West
		if (this->matrixPointer[Generic::iMod(elem - 1, tElem)] > 127.5f) n++;

		/// North East
		if (this->matrixPointer[Generic::iMod(elem - this->matrixSize + 1, tElem)] > 127.5f) n++;

		/// South East
		if (this->matrixPointer[Generic::iMod(elem + this->matrixSize + 1, tElem)] > 127.5f) n++;

		/// South West
		if (this->matrixPointer[Generic::iMod(elem + this->matrixSize - 1, tElem)] > 127.5f) n++;

		/// North West
		if (this->matrixPointer[Generic::iMod(elem - this->matrixSize - 1, tElem)] > 127.5f) n++;

		return n;

	}

	//////////////////////////////////////////////////
	// Conways Game of Life Generator
	//
	void Matrix::gameOfLife(uint8_t tHold)
	{
		/// Easier local reference
		auto elements = this->matrixSize * this->matrixSize;

		/// Second array
		float *temp = new float[elements];

		/// CILK intel
#pragma omp parallel for
		for (auto i = 0; i < elements; i++)
		{
			/// Check Neighbours
			auto n = gameOfLifeNeighbours(i,elements);

			if(n < 3)
			{
				temp[i] = --this->matrixPointer[i];
			}
			else if (n == 3)
			{
				temp[i] = this->matrixPointer[i];
			}
			else if (n > 3)
			{
				temp[i] = ++this->matrixPointer[i];
			}
		}
		delete matrixPointer;
		this->matrixPointer = temp;		
	}


	//////////////////////////////////////////////////
	// Accessor Methods
	//
	float* Matrix::getArray() const
	{
		return matrixPointer;
	}

}
