// 2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "matrix.h"

double fixTime(matrix *m, bool parallel) {
	auto time = omp_get_wtime();
	double det = parallel ? m->getDeterminantParallel() : m->getDeterminant();
	time = omp_get_wtime() - time;
	cout << "determinant = " << det << "; time = " << time << endl;
	return time;
}
bool isM4 = false;

void start(char* path) {
	matrix::setNotationFromOne(!isM4);
	matrix* m;
	double time1, time2;
	m = matrix::parse(path);
	cout << "no parallel" << endl;
	time1 = fixTime(m, false);
	m->~matrix();

	matrix::setNotationFromOne(!isM4);
	m = matrix::parse(path);
	cout << "with parallel" << endl;
	time2 = fixTime(m, true);
	m->~matrix();

	cout << "Выигрыш по скорости:  " << time1 - time2 << endl << endl;
}

int main()
{
	setlocale(LC_ALL, "rus");
	char* m1 = "matr1.txt";
	/*matrix m = *matrix::parse(m1);
	m.printFile();*/
	char* m2 = "matr2.txt";
	char* m3 = "matr3.txt";
	char* m4 = "matr4.txt";

	cout << "m1" << endl;
	start(m1);

	cout << "m2" << endl;
	start(m2);

	//cout << "m3" << endl;
	//start(m3);

	isM4 = true;
	cout << "m4" << endl;
	start(m4);
	isM4 = false;
	while (getchar() != 'q')
	{
		cout << "m1" << endl;
		start(m1);

		cout << "m2" << endl;
		start(m2);

		/*cout << "m3" << endl;
		start(m3);*/

		cout << "m4" << endl;
		isM4 = true;
		start(m4);
		isM4 = false;
	}

    return 0;
}

