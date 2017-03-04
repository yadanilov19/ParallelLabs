// 2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "matrix.h"

double fixTime(matrix *m, bool parallel) {
	//m->printFile();
	auto time = omp_get_wtime();
	double det = parallel ? m->getDeterminantParallel() : m->getDeterminant();
	time = omp_get_wtime() - time;
	cout << "determinant = " << det << "; time = " << time << endl;
	//m->printFile();
	return time;
}

void start() {
	matrix m = matrix::parse("C:\\Users\\localadmin\\Source\\Repos\\ParallelLabs\\parralels\\Debug\\test.txt");
	cout << "no parallel" << endl;
	//omp_set_num_threads(2);
	fixTime(&m, false);
	cout << "with parallel" << endl;
	fixTime(&m, true);
}

int main()
{
	setlocale(LC_ALL, "rus");
	start();
	while (getchar())
	{
		start();
	}
    return 0;
}

