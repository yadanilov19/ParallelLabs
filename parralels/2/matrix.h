#pragma once
#include <omp.h>

using namespace std;

class matrix
{
private:
	int n = 0;
	float** data;
	void toOneDiagonalMatrix();
	void rowSubstractionForTriangle(int index);
	void toTriangleMatrix();
	void rowSubstractionForTriangleParallel(int index);
	void toTriangleMatrixParallel();
	void swapRows(int index);
	float getMultiplyDiagonalElements();
public:

	matrix(int _n);
	void print();
	void printFile();
	float getDeterminant();
	float getDeterminantParallel();
	static matrix parse(char* filename);
	~matrix();
};


