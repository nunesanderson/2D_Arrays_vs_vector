// 2DArraysPointers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <stdio.h>
#include <vector>
using namespace std;


void runTest(int n, double &timeVect, double &timeArrPointer,double &timeArrIndices){

	time_t start, end;

	////////////////////////////////////////////////////
	// Creating the arrays
	////////////////////////////////////////////////////
	
	double** arrA;
	double** arrB;
	double** arrC;

	vector<vector<double>> vecA;
	vecA.resize(n, vector<double>(n, n));
	vector<vector<double>> vecB;
	vecB.resize(n, vector<double>(n, n));
	vector<vector<double>> vecC;
	vecC.resize(n, vector<double>(n, n));


	arrA = new double*[n];
	arrB = new double*[n];
	arrC = new double*[n];

	for (int x = 0; x<n; x++)
	{
		arrA[x] = new double[n];
		arrB[x] = new double[n];
		arrC[x] = new double[n];
	}

	////////////////////////////////////////////////////
	//Populating the arrays
	////////////////////////////////////////////////////

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			arrA[i][j] = 1;
			arrB[i][j] = 1;
			arrC[i][j] = 0;

			vecA[i][j] = 1;
			vecB[i][j] = 1;
			vecC[i][j] = 0;
		}
	}

	////////////////////////////////////////////////////
	//Multiplicating the arrays (vectors)
	////////////////////////////////////////////////////
	const clock_t begin_time = clock();

	for (int i = 0; i<n; ++i)
		for (int j = 0; j<n; ++j)
			for (int k = 0; k<n; ++k)
			{
				vecC[i][j] += vecA[i][k] * vecB[k][j];
			}

	time(&end);
	timeVect = float(clock() - begin_time) / CLOCKS_PER_SEC;

	////////////////////////////////////////////////////
	//Multiplicating the arrays (indices)
	////////////////////////////////////////////////////
	const clock_t begin_time_1 = clock();

	for (int i = 0; i<n; ++i)
		for (int j = 0; j<n; ++j)
			for (int k = 0; k<n; ++k)
			{
				arrC[i][j] += arrA[i][k] * arrB[k][j];
			}

	time(&end);
	timeArrIndices = float(clock() - begin_time_1) / CLOCKS_PER_SEC;

	////////////////////////////////////////////////////
	//Multiplicating the arrays (pointers)
	////////////////////////////////////////////////////
	const clock_t begin_time_2 = clock();

	for (int i = 0; i<n; ++i)
		for (int j = 0; j<n; ++j)
			for (int k = 0; k<n; ++k)
			{
				*(*(arrC + i) + j) += *(*(arrA + i) + j)*(*(*(arrB + k) + j));
			}

	timeArrPointer = float(clock() - begin_time_2) / CLOCKS_PER_SEC;

	////////////////////////////////////////////////////
	//Destroying the arrays
	////////////////////////////////////////////////////

	for (int x = 0; x < n; x++)
	{
		delete[] arrA[x];
		delete[] arrB[x];
		delete[] arrC[x];

	}

	delete[]arrA;
	delete[]arrB;
	delete[]arrC;
}


int _tmain(int argc, _TCHAR* argv[])
{
	double timeVect, timeArrPointer, timeArrIndices;
	
	vector<int> ns = { 10, 20, 40,50,60,70, 80,90, 100,110,120,130,140, 150, 200, 250, 300, 350, 400, 450, 500, 1000, 1500,2000,2500,3000};
	
	printf("N\t\tVector\t\t\tArray(Pointer)\t\tArray(Index)\n");
	
	for  each (int n in ns)
	{
		const clock_t begin_time = clock();
		runTest(n, timeVect, timeArrPointer, timeArrIndices);
		printf("%d\t\t%10.8f\t\t%10.8f\t\t%10.8f\n", n, timeVect, timeArrPointer, timeArrIndices);
	}

	printf("Done!");
	getchar();

	return 0;
}

