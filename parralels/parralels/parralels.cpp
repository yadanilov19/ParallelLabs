// parralels.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "table_printer.h"
#include "parralels.h"
using namespace std;
using namespace bprinter;

//1 task
void first() {
#pragma omp parallel num_threads(5)
	printf("hello world\n");
}

void secondHelper(char* str, TablePrinter *tp, function<void(int,int)> a) {
	double timeStatic = omp_get_wtime(),
		timeDynamic,
		timeGuided,
		timeRuntime;
	int n = 10;
#pragma omp parallel  for schedule(static) firstprivate(n)
	for (int i = 0; i < n; i++)
	{
		a(i,n);
	}

	timeStatic = omp_get_wtime() - timeStatic;
	timeDynamic = omp_get_wtime();
#pragma omp parallel  for schedule(dynamic) firstprivate(n)
	for (int i = 0; i < n; i++)
	{
		a(i,n);
	}
	timeDynamic = omp_get_wtime() - timeDynamic;
	timeGuided = omp_get_wtime();
#pragma omp parallel  for schedule(guided) firstprivate(n)
	for (int i = 0; i < n; i++)
	{
		a(i,n);
	}
	timeGuided = omp_get_wtime() - timeGuided;

	timeRuntime = omp_get_wtime();
#pragma omp parallel  for schedule(runtime) firstprivate(n)
	for (int i = 0; i < n; i++)
	{
		a(i,n);
	}
	timeRuntime = omp_get_wtime() - timeRuntime;


	*tp << str << timeStatic << timeDynamic << timeGuided << timeRuntime;

}
//
void second() {
	//Инициализация таблицы для вывода
	TablePrinter tp(&cout);
	tp.AddColumn("Name", 40);
	tp.AddColumn("static", 10);
	tp.AddColumn("dynamic", 10);
	tp.AddColumn("guided", 10);
	tp.AddColumn("runtime", 10);
	tp.PrintHeader();

	secondHelper("Iterations with Normal Distrib", &tp, [](int i, int n) {
		Sleep(1);
	});
	
	secondHelper("Iterations with i % 2 == 0 ", &tp, [](int i, int n) {
		if (i % 2 == 0)
			Sleep(100);
		else
			Sleep(10);
	});
	secondHelper("Iterations with i < n / 2 ", &tp, [](int i, int n) {
		if (i <= n / 2)
			Sleep(100);
		else
			Sleep(10);
	});
	tp.PrintFooter();
}
//

void thirdInit(int* A, int n) {
	for (int i = 0; i < n; i++)
	{
		A[i] = rand();
	}
}
void third() {
	TablePrinter tp(&cout);
	tp.AddColumn("Name", 40);
	tp.AddColumn("time", 10);
	tp.PrintHeader();

	const int n = 500; 
	int A[n], 
		sumCriticalSetion = 0,
		sumReduction = 0;
	double timeCritSec = 0,
		timeReduction = 0;

	thirdInit(A, n);

	timeCritSec = omp_get_wtime();
#pragma omp parallel for firstprivate(n)
	for (int i = 0; i < n; i++)
	{
#pragma omp critical
		{
			sumCriticalSetion += A[i];
		} 
	}
	timeCritSec = omp_get_wtime() - timeCritSec;
	tp << "Critical Section" << timeCritSec;

	timeReduction = omp_get_wtime();
#pragma omp parallel for reduction(+:sumReduction) firstprivate(n)
	for (int i = 0; i < n; i++)
	{
		sumReduction += A[i];
	}
	timeReduction = omp_get_wtime() - timeReduction;
	tp << "Reduction" << timeReduction;

	tp.PrintFooter();
}
//
void fourth() {
#pragma omp parallel num_threads(10)
	{
		float a = rand();
		if (a < 0.4)
		{
			Sleep(100);
		}
		else
		{
			Sleep(10);
		}

#pragma omp barrier
		int threadNum = omp_get_thread_num();
		printf("%f num thread %i \n", a, threadNum);
	}
}
//
void fifth() {
	//???
}
//
int main()
{
	first();
	second();
	third();
	fourth();
	fifth();

	return 0;
}

