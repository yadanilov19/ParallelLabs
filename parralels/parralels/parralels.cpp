// parralels.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "parralels.h"
using namespace std;

//1 task
void first() {
#pragma omp parallel num_threads(5)
	printf("hello world\n");
}
//
//void secondHelper(char* str, TablePrinter *tp, function<void(int, int)> a) {
//	double timeStatic = omp_get_wtime(),
//		timeDynamic,
//		timeGuided,
//		timeRuntime;
//	int n = 1000;
//#pragma omp parallel  for schedule(static) firstprivate(n)
//	for (int i = 0; i < n; i++)
//	{
//		a(i, n);
//	}
//
//	timeStatic = omp_get_wtime() - timeStatic;
//	timeDynamic = omp_get_wtime();
//#pragma omp parallel  for schedule(dynamic) firstprivate(n)
//	for (int i = 0; i < n; i++)
//	{
//		a(i, n);
//	}
//	timeDynamic = omp_get_wtime() - timeDynamic;
//	timeGuided = omp_get_wtime();
//#pragma omp parallel  for schedule(guided) firstprivate(n)
//	for (int i = 0; i < n; i++)
//	{
//		a(i, n);
//	}
//	timeGuided = omp_get_wtime() - timeGuided;
//
//	timeRuntime = omp_get_wtime();
//#pragma omp parallel  for schedule(runtime) firstprivate(n)
//	for (int i = 0; i < n; i++)
//	{
//		a(i, n);
//	}
//	timeRuntime = omp_get_wtime() - timeRuntime;
//
//
//	*tp << str << timeStatic << timeDynamic << timeGuided << timeRuntime;
//
//}
////
//void second() {
//	//Инициализация таблицы для вывода
//	TablePrinter tp(&cout);
//	tp.AddColumn("Name", 40);
//	tp.AddColumn("static", 10);
//	tp.AddColumn("dynamic", 10);
//	tp.AddColumn("guided", 10);
//	tp.AddColumn("runtime", 10);
//	tp.PrintHeader();
//
//	secondHelper("Iterations with Normal Distrib", &tp, [](int i, int n) {
//		
//	});
//
//	secondHelper("Iterations with i % 2 == 0 ", &tp, [](int i, int n) {
//		if (i % 2 == 0)
//			Sleep(1);
//	});
//	secondHelper("Iterations with i < n / 2 ", &tp, [](int i, int n) {
//		if (i <= n / 2)
//			Sleep(1);
//	});
//	tp.PrintFooter();
//}
////
//
//void thirdInit(int* A, int n) {
//	for (int i = 0; i < n; i++)
//	{
//		A[i] = rand();
//	}
//}
//void third() {
//	TablePrinter tp(&cout);
//	tp.AddColumn("Name", 40);
//	tp.AddColumn("time", 10);
//	tp.PrintHeader();
//
//	const int n = 500;
//	int A[n],
//		sumCriticalSetion = 0,
//		sumReduction = 0;
//	double timeCritSec = 0,
//		timeReduction = 0;
//
//	thirdInit(A, n);
//
//	timeCritSec = omp_get_wtime();
//#pragma omp parallel for firstprivate(n)
//	for (int i = 0; i < n; i++)
//	{
//#pragma omp critical
//		{
//			sumCriticalSetion += A[i];
//		}
//	}
//	timeCritSec = omp_get_wtime() - timeCritSec;
//	tp << "Critical Section" << timeCritSec;
//
//	timeReduction = omp_get_wtime();
//#pragma omp parallel for reduction(+:sumReduction) firstprivate(n)
//	for (int i = 0; i < n; i++)
//	{
//		sumReduction += A[i];
//	}
//	timeReduction = omp_get_wtime() - timeReduction;
//	tp << "Reduction" << timeReduction;
//
//	tp.PrintFooter();
//}
////
//void fourth() {
//#pragma omp parallel num_threads(3)
//	{
//		printf("first\n");
//#pragma omp barrier
//		printf("second\n");
//	}
//}
////
//
//
//const long n = 10000;
//int A[n][n];
//void fithInit() {
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//			A[i][j] = 1;
//		}
//	}
//}
//void printTable(double time) {
//	printf("%f timeElapsed", time);
//	TablePrinter tp(&cout);
//	for (int i = 0; i < 10; i++)
//	{
//		tp.AddColumn("#", 10);
//	}
//	tp.PrintHeader();
//	for (long i = n - 10; i < n; i++)
//	{
//		for (long j = n - 10; j < n; j++)
//		{
//			tp << A[i][j];
//		}
//	}
//	tp.PrintFooter();
//}
//void fifth() {
//	fithInit();
//	double timeParallel, timeSequance;
//	omp_set_num_threads(4);
//	//parallel
//	timeParallel = omp_get_wtime();
//	for (long numDiagonal = 4; numDiagonal < n * 2 - 1 ; numDiagonal++)
//	{
//		long j = max(2, numDiagonal - n + 1);
//#pragma omp parallel for firstprivate(n)
//		for (; j <= min(numDiagonal - 2, n - 1); j++)
//		{
//			A[j][numDiagonal - j] = A[j - 2][numDiagonal - j] + A[j][numDiagonal - j - 2];
//		}
//	}
//	timeParallel = omp_get_wtime() - timeParallel;
//	printTable(timeParallel);
//	
//	
//	fithInit();
//	timeSequance = omp_get_wtime();
//	//seq
//	for (long i = 2; i < n; i++)
//	{
//		for (long j = 2; j < n; j++)
//		{
//			A[i][j] = A[i - 2][j] + A[i][j - 2];
//		}
//	}
//	timeSequance = omp_get_wtime() - timeSequance;
//	printTable(timeSequance);
//
//}
//
int main()
{
	first();
	////second();
	//third();
	//fourth();
	//fifth();

	return 0;
}

