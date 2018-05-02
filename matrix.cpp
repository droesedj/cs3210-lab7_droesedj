/**
 *	LAB WEEK 2: MATRIX CLASS
 *	CS3210
 *	@author Dennis Droese
 *	@date March 14, 2018
 *  @file matrix.cpp
 */


#include "matrix.h"
#include <string>
#include <cmath>

// Parameterized constructor
matrix::matrix(unsigned int rows, unsigned int cols):rows(rows),cols(cols) 
{  
	if (rows < 1 || cols < 1)
	{
		throw matrixException("p-constructor bad arguments");
	} else {

		the_matrix = new double*[rows];

		for(unsigned int i = 0; i < rows; i++){
			the_matrix[i] = new double[cols];
		}

		clear();
	}
}

// Copy constructor
matrix::matrix(const matrix& from):rows(from.rows),cols(from.cols)
{
	if (rows < 1 || cols < 1)
	{
		throw matrixException("p-constructor bad arguments");
	} else {

		the_matrix = new double*[rows];

		for(unsigned int i = 0; i < rows; i++){
			the_matrix[i] = new double[cols];
		}

		clear();
	}

	// Copy all of the data of the old matrix to the new one.
	for(unsigned int x = 0; x < rows; x++){
		for(unsigned int y = 0; y < cols; y++){
			the_matrix[x][y] = from.the_matrix[x][y];
		}
	}
}

// Destructor
matrix::~matrix()
{
	//Make sure there is actually something to delete...
	if(the_matrix != nullptr){
		for(unsigned int i = 0; i < rows; i++){
			delete[] the_matrix[i];
		}

		delete[] the_matrix;
	}
}

// Assignment operator
matrix& matrix::operator=(const matrix& rhs)
{

	// Delete the existing matrix since it's getting reassigned.
	if(the_matrix != nullptr){
		for(unsigned int i = 0; i < rows; i++){
			delete the_matrix[i];
		}

		delete the_matrix;
	}

	the_matrix = new double*[rows];

	for(unsigned int i = 0; i < rows; i++){
		the_matrix[i] = new double[cols];
	}

	clear();

	rows = rhs.rows;
	cols = rhs.cols;

	// Copy all of the data of the old matrix to the new one.
	for(unsigned int x = 0; x < rows; x++){
		for(unsigned int y = 0; y < cols; y++){
			the_matrix[x][y] = rhs.the_matrix[x][y];
		}
	}

	return *this;
}

// Named constructor (static)
matrix matrix::identity(unsigned int size)
{
	// use p-constructor
	matrix ret(size,size);

	for(int unsigned i = 0; i < size; i++){
		ret[i][i] = 1;
	}

	return ret;
}


// Binary operations
matrix matrix::operator+(const matrix& rhs) const
{
	if(rhs.rows != rows || rhs.cols != cols){
		throw matrixException("Attempted to add two matrices with different sizes!");
	}

	matrix retVal(rhs);

	for(unsigned int x = 0; x < rows; x++){
		for(unsigned int y = 0; y < cols; y++){
			retVal[x][y] = retVal[x][y] + the_matrix[x][y];
		}
	}

	return retVal;
}


matrix matrix::operator*(const matrix& rhs) const
{
	if(cols != rhs.rows){
		throw matrixException("Attempted to multiply incompatible matrices.");
	}

	matrix retVal(rows,rhs.cols);

	for(unsigned int i = 0; i < rows; i++){
		for(unsigned int j = 0; j < rhs.cols; j++){
			double sum = 0.0;
			for(unsigned int k = 0; k < cols; k++){
				sum = sum + (the_matrix[i][k] * rhs[k][j]);
			}
			retVal[i][j] = sum;
		}
	}

	return retVal;
}

matrix matrix::operator*(const double scale) const
{
	matrix retVal(*this);

	// Multiply every entry in the matrix by the scale.
	for(unsigned int x = 0; x < rows; x++){
		for(unsigned int y = 0; y < cols; y++){
			retVal[x][y] = the_matrix[x][y] * scale;
		}
	}

	return retVal;
}


// Unary operations
matrix matrix::operator~() const
{
	matrix retVal(cols, rows);

	// Swap the axis of the matrix.
	for(unsigned int x = 0; x < cols; x++){
		for(unsigned int y = 0; y < rows; y++){
			retVal[x][y] = the_matrix[y][x];
		}
	}

	return retVal;
}
	

void matrix::clear()
{
	// make sure there are valid doubles to clear.
	if(rows == 0 || cols == 0 || the_matrix == nullptr){
		return;
	}

	double* ptr;

	for(unsigned int x = 0; x < rows; x++){
		ptr = the_matrix[x];
		for(unsigned int y = 0; y < cols; y++){
			ptr[y] = 0.0;
		}
	}

	return;
}

double* matrix::operator[](unsigned int row)
{


	for(unsigned int x = 0; x < row; x++){
		if(the_matrix[x] == nullptr) {
			throw matrixException("Specified index out of range.");
		}
	}

	return the_matrix[row];
}

double* matrix::operator[](unsigned int row) const
{
	for(unsigned int x = 0; x < row; x++){
		if(the_matrix[x] == nullptr) {
			throw matrixException("Specified index out of range.");
		}
	}

	return the_matrix[row];
}


std::ostream& matrix::out(std::ostream& os) const
{
	if(the_matrix == nullptr || rows == 0 || cols == 0){
		os << "Empty or invalid matrix.\n";
	} else {
	os << '[';

	for(unsigned int x = 0; x < rows; x++){
		os << "[\t";
		for(unsigned int y = 0; y < cols; y++){
			os << (double)(the_matrix[x][y]) << '\t';
		}
		os << ']';

		if(x < rows - 1){
			os << '\n';
		}
	}

	os << "]\n";
	}
	return os;	
}
//
//  ____________
//0 | 0  1  2  3
//1 | 4  5  6  7
//2 | 8  9 10 11
//3 |12 13 14 15

// ASSUMES 4x4 MATRIX!!!
matrix matrix::inverse(matrix mat, unsigned int size){

	matrix invOut(4,4);

	 double m[] =   { mat[0][0], mat[0][1], mat[0][2], mat[0][3],
			 	 	  mat[1][0], mat[1][1], mat[1][2], mat[1][3],
					  mat[2][0], mat[2][1], mat[2][2], mat[2][3],
					  mat[3][0], mat[3][1], mat[3][2], mat[3][3]};

	 double inv[16];
	 double det;

	 inv[ 0] =  m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
	 inv[ 4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
	 inv[ 8] =  m[4] * m[ 9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[ 9];
	 inv[12] = -m[4] * m[ 9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[ 9];
	 inv[ 1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
	 inv[ 5] =  m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
	 inv[ 9] = -m[0] * m[ 9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[ 9];
	 inv[13] =  m[0] * m[ 9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[ 9];
	 inv[ 2] =  m[1] * m[ 6] * m[15] - m[1] * m[ 7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[ 7] - m[13] * m[3] * m[ 6];
	 inv[ 6] = -m[0] * m[ 6] * m[15] + m[0] * m[ 7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[ 7] + m[12] * m[3] * m[ 6];
	 inv[10] =  m[0] * m[ 5] * m[15] - m[0] * m[ 7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[ 7] - m[12] * m[3] * m[ 5];
	 inv[14] = -m[0] * m[ 5] * m[14] + m[0] * m[ 6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[ 6] + m[12] * m[2] * m[ 5];
	 inv[ 3] = -m[1] * m[ 6] * m[11] + m[1] * m[ 7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[ 9] * m[2] * m[ 7] + m[ 9] * m[3] * m[ 6];
	 inv[ 7] =  m[0] * m[ 6] * m[11] - m[0] * m[ 7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[ 8] * m[2] * m[ 7] - m[ 8] * m[3] * m[ 6];
	 inv[11] = -m[0] * m[ 5] * m[11] + m[0] * m[ 7] * m[ 9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[ 9] - m[ 8] * m[1] * m[ 7] + m[ 8] * m[3] * m[ 5];
	 inv[15] =  m[0] * m[ 5] * m[10] - m[0] * m[ 6] * m[ 9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[ 9] + m[ 8] * m[1] * m[ 6] - m[ 8] * m[2] * m[ 5];



	 det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	 if(det == 0)
		 // it's no good
	     return mat;



	 det = 1.0 / det;


	     invOut[0][0] = inv[0] * det;
	     invOut[0][1] = inv[1] * det;
	     invOut[0][2] = inv[2] * det;
	     invOut[0][3] = inv[3] * det;
	     invOut[1][0] = inv[4] * det;
	     invOut[1][1] = inv[5] * det;
	     invOut[1][2] = inv[6] * det;
	     invOut[1][3] = inv[7] * det;
	     invOut[2][0] = inv[8] * det;
	     invOut[2][1] = inv[9] * det;
	     invOut[2][2] = inv[10] * det;
	     invOut[2][3] = inv[11] * det;
	     invOut[3][0] = inv[12] * det;
	     invOut[3][1] = inv[13] * det;
	     invOut[3][2] = inv[14] * det;
	     invOut[3][3] = inv[15] * det;


	 return invOut;
}


// Global insertion and operator
std::ostream& operator<<(std::ostream& os, const matrix& rhs)
{
	return rhs.out(os);
}

// Global scalar multiplication
matrix operator*(const double scale, const matrix& rhs)
{
	matrix retval(rhs);
	retval = retval * scale;
	return retval;
}


