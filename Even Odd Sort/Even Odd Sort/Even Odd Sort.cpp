// Even Odd Sort.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include<stdio.h>    
#include<string.h>   
#include <iostream>
#include "omp.h"
#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;

fstream FileResult;

void input_text()
{
	cout << "\n" << setw(45) << "Число потоков:2" << setw(27) << "Число потоков:4" << setw(25) << "Число потоков:8" << setw(25) << "Число потоков:16" << setw(25) << "Число потоков:32" << endl;
	cout << "\n" << setw(20) << "Время" << setw(29) << "Время   Ускорение" << setw(25) << "Время   Ускорение" << setw(23) << "Время   Ускорение" << setw(23) << "Время   Ускорение" << setw(23) << "Время   Ускорение" << endl;
}

int* CaseOfArray(int* Arr100, int* Arr1000, int* Arr10000, int* Arr100000, int* Arr1000000, int NumberOfArr)
{
	int* ArrNew = new int[NumberOfArr];
	switch (NumberOfArr)
	{
	case 100:
		memcpy(ArrNew, Arr100, NumberOfArr*sizeof(int));
		return  ArrNew;
		break;
	case 1000:
		memcpy(ArrNew, Arr1000, NumberOfArr * sizeof(int));
		return  ArrNew;
		break;
	case 10000:
		memcpy(ArrNew, Arr10000, NumberOfArr * sizeof(int));
		return  ArrNew;
		break;
	case 100000:
		memcpy(ArrNew, Arr100000, NumberOfArr * sizeof(int));
		return  ArrNew;
		break;
	case 1000000: memcpy(ArrNew, Arr1000000, NumberOfArr * sizeof(int));
		return  ArrNew;;
		break;
	default:
		cout << "Error";
		break;
	}
}
int *input_array(int CountOfElem)
{
	int* Arr = new int[CountOfElem];
	for (int i = 0; i < CountOfElem; i++)
	{
		Arr[i] = rand() % 100;
	}
	return  Arr;
}

void swap(int *a, int *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

void Odd_even_sort_parallel_static(int* Arr, int CountOfElem, int CountOfStream , double SeqTime)
{
	FileResult.open("FileResult.txt", ios::in | ios::app);
	omp_set_num_threads(CountOfStream);
	bool sorted = false;
	double start_time, end_time;
	int SizeOfBlock = CountOfElem / CountOfStream;
	start_time = omp_get_wtime();// Время начала сортировки
	while (!sorted)
	{
		sorted = true;
#pragma omp parallel for schedule(static,SizeOfBlock)
		for (int i = 1; i< CountOfElem - 1; i += 2)
		{
			if (Arr[i]>Arr[i + 1])
			{
				swap(&Arr[i], &Arr[i + 1]);
				sorted = false;
			}
		}
#pragma omp parallel for schedule(static,SizeOfBlock)
		for (int i = 0; i< CountOfElem - 1; i += 2)
		{
			if (Arr[i]>Arr[i + 1])
			{
				swap(&Arr[i], &Arr[i + 1]);
				sorted = false;
			}
		}
	}
	end_time = omp_get_wtime(); // Время конца сортировки
	double ParTime = end_time - start_time;//Время выполнения параллельной сортировки
	double Acceleration = SeqTime / (end_time - start_time);//Время ускорения
	cout << fixed << setprecision(5) << ParTime << "  " << fixed << setprecision(5) << Acceleration << setw(15);//Вывод в консоль
	FileResult << "\n" << fixed << setprecision(5) << ParTime << "  " << fixed << setprecision(5) << Acceleration << setw(15);//Запись в файл
	FileResult.close();
	if (CountOfElem <= 10)
	{
		cout << endl << endl << "Вывод отсортированного массива ->";
		for (int i = 0; i < CountOfElem; i++)
		{
			cout << Arr[i] << "  ";
		}
	}
}

void Odd_even_sort_parallel_guided(int* Arr, int CountOfElem, int CountOfStream, double SeqTime)
{
	FileResult.open("FileResult.txt", ios::in | ios::app);
	omp_set_num_threads(CountOfStream);
	bool sorted = false;
	double start_time, end_time;
	int SizeOfBlock = CountOfElem / CountOfStream;
	start_time = omp_get_wtime();// Время начала сортировки
	while (!sorted)
	{
		sorted = true;
#pragma omp parallel for schedule(guided,SizeOfBlock)
		for (int i = 1; i< CountOfElem - 1; i += 2)
		{
			if (Arr[i]>Arr[i + 1])
			{
				swap(&Arr[i], &Arr[i + 1]);
				sorted = false;
			}
		}
#pragma omp parallel for schedule(guided,SizeOfBlock)
		for (int i = 0; i< CountOfElem - 1; i += 2)
		{
			if (Arr[i]>Arr[i + 1])
			{
				swap(&Arr[i], &Arr[i + 1]);
				sorted = false;
			}
		}
	}
	end_time = omp_get_wtime(); // Время конца сортировки
	double ParTime = end_time - start_time;//Время выполнения параллельной сортировки
	double Acceleration = SeqTime / (end_time - start_time);//Время ускорения
	cout << fixed << setprecision(5) << ParTime << "  " << fixed << setprecision(5) << Acceleration << setw(15);//Вывод в консоль
	FileResult << "\n" << fixed << setprecision(5) << ParTime << "  " << fixed << setprecision(5) << Acceleration << setw(15);//Запись в файл
	FileResult.close();
	if (CountOfElem <= 10)
	{
		cout << endl << endl << "Вывод отсортированного массива ->";
		for (int i = 0; i < CountOfElem; i++)
		{
			cout << Arr[i];
		}
	}
}

void Odd_even_sort_parallel_runtime(int* Arr, int CountOfElem, int CountOfStream, double SeqTime)
{
	FileResult.open("FileResult.txt", ios::in | ios::app);
	omp_set_num_threads(CountOfStream);
	bool sorted = false;
	double start_time, end_time;
	int SizeOfBlock = CountOfElem / CountOfStream;
	start_time = omp_get_wtime();// Время начала сортировки
	while (!sorted)
	{
		sorted = true;
#pragma omp parallel for schedule(runtime) 
		for (int i = 1; i< CountOfElem - 1; i += 2)
		{
			if (Arr[i]>Arr[i + 1])
			{
				swap(&Arr[i], &Arr[i + 1]);
				sorted = false;
			}
		}
#pragma omp parallel for schedule(runtime)
		for (int i = 0; i< CountOfElem - 1; i += 2)
		{
			if (Arr[i]>Arr[i + 1])
			{
				swap(&Arr[i], &Arr[i + 1]);
				sorted = false;
			}
		}
	}
	end_time = omp_get_wtime(); // Время конца сортировки
	double ParTime = end_time - start_time;//Время выполнения параллельной сортировки
	double Acceleration = SeqTime / (end_time - start_time);//Время ускорения
	cout << fixed << setprecision(5) << ParTime << "  " << fixed << setprecision(5) << Acceleration << setw(15);//Вывод в консоль
	FileResult << "\n" << fixed << setprecision(5) << ParTime << "  " << fixed << setprecision(5) << Acceleration << setw(15);//Запись в файл
	if (CountOfElem <= 10)
	{
		cout << endl << endl << "Вывод отсортированного массива ->";
		for (int i = 0; i < CountOfElem; i++)
		{
			cout << Arr[i];
		}
	}
}

void Odd_even_sort_parallel_dynamic(int* Arr, int CountOfElem, int CountOfStream, double SeqTime)
{
	FileResult.open("FileResult.txt", ios::in | ios::app);
	omp_set_num_threads(CountOfStream);
	bool sorted = false;
	double start_time, end_time;
	int SizeOfBlock = CountOfElem / CountOfStream;
	start_time = omp_get_wtime();// Время начала сортировки
	while (!sorted)
	{
		sorted = true;
#pragma omp parallel for schedule(dynamic,SizeOfBlock)
		for (int i = 1; i< CountOfElem - 1; i += 2)
		{
			if (Arr[i]>Arr[i + 1])
			{
				swap(&Arr[i], &Arr[i + 1]);
				sorted = false;
			}
		}
#pragma omp parallel for  schedule(dynamic,SizeOfBlock)
		for (int i = 0; i< CountOfElem - 1; i += 2)
		{
			if (Arr[i]>Arr[i + 1])
			{
				swap(&Arr[i], &Arr[i + 1]);
				sorted = false;
			}
		}
	}
	end_time = omp_get_wtime(); // Время конца сортировки
	double ParTime = end_time - start_time;//Время выполнения параллельной сортировки
	double Acceleration = SeqTime / (end_time - start_time);//Время ускорения
	cout << fixed << setprecision(5) << ParTime << "  " << fixed << setprecision(5) << Acceleration << setw(15);//Вывод в консоль
	FileResult << "\n" << fixed << setprecision(5) << ParTime << "  " << fixed << setprecision(5) << Acceleration << setw(15);//Запись в файл
	FileResult.close();
	if (CountOfElem <= 10)
	{
		cout << endl << endl << "Вывод отсортированного массива ->";
		for (int i = 0; i < CountOfElem; i++)
		{
			cout << Arr[i];
		}
	}
}

void Odd_even_sort_parallel_for(int* Arr, int CountOfElem, int CountOfStream, double SeqTime)
{
	FileResult.open("FileResult.txt", ios::in | ios::app);
	omp_set_num_threads(CountOfStream);
	bool sorted = false;
	double start_time, end_time;
	int SizeOfBlock = CountOfElem / CountOfStream;
	start_time = omp_get_wtime();// Время начала сортировки
	while (!sorted)
	{
		sorted = true;
#pragma omp parallel for 
		for (int i = 1; i< CountOfElem - 1; i += 2)
		{
			if (Arr[i]>Arr[i + 1])
			{
				swap(&Arr[i], &Arr[i + 1]);
				sorted = false;
			}
		}
#pragma omp parallel for
		for (int i = 0; i< CountOfElem - 1; i += 2)
		{
			if (Arr[i]>Arr[i + 1])
			{
				swap(&Arr[i], &Arr[i + 1]);
				sorted = false;
			}
		}
	}
	end_time = omp_get_wtime(); // Время конца сортировки
	double ParTime = end_time - start_time;//Время выполнения параллельной сортировки
	double Acceleration = SeqTime / (end_time - start_time);//Время ускорения
	cout << fixed << setprecision(5) << ParTime << "  " << fixed << setprecision(5) << Acceleration << setw(15);//Вывод в консоль
	FileResult << "\n" << fixed << setprecision(5) << ParTime << "  " << fixed << setprecision(5) << Acceleration << setw(15);//Запись в файл
	FileResult.close();
	if (CountOfElem <= 10)
	{
		cout << endl << endl << "Вывод отсортированного массива ->";
		for (int i = 0; i < CountOfElem; i++)
		{
			cout << Arr[i];
		}
	}
}

double Odd_even_sort_sequential(int* Arr , int CountOfElem)
{
	FileResult.open("FileResult.txt", ios::in | ios::app);
	int i = 0;
	bool sorted = false;
	double start_time, end_time;
	bool fl = true;
		start_time = omp_get_wtime();// Время начала сортировки
		while (!sorted)
		{
			sorted = true;
			if (i % 2 == 1)
			{
				for (int i = 1; i < CountOfElem - 1; i += 2)
				{

					if (Arr[i] > Arr[i + 1])
					{
						swap(&Arr[i], &Arr[i + 1]);
						sorted = false;
					}
				}
			}
			if (i % 2 == 0)
				for (int i = 0; i < CountOfElem - 1; i += 2)
				{

					if (Arr[i] > Arr[i + 1])
					{
						swap(&Arr[i], &Arr[i + 1]);
						sorted = false;
					}
				}
			i++;
		}
		end_time = omp_get_wtime(); // Время конца сортировки
		double SeqTime = end_time - start_time;//Время выполнения последовательной сортировки 
		cout << "\n" << CountOfElem << "		" << fixed << setprecision(5) << SeqTime << setw(15);
		FileResult << "\n" << CountOfElem << "		" << fixed << setprecision(5) << SeqTime;//Запись в файл
		FileResult.close();
	if (CountOfElem <= 10)
	{
		cout << endl << endl << "Вывод отсортированного массива ->";
		for (int i = 0; i < CountOfElem; i++)
		{
			cout << Arr[i] << "  ";
		}
		
	}
	return SeqTime;
}

void AllSort()
{
		int CountOfElem = 1000000;
		double SeqTime;//Время последовательной сортировки
		int stream = 2; //Кол-во потоков
		int *Arr100 = input_array(100);
		int *Arr1000 = input_array(1000);
		int *Arr10000 = input_array(10000);
		int *Arr100000 = input_array(100000);
		cout << "\n" << "\n";
		cout << "Последовательный алгоритм			static - Параллельный алгоритм" << endl;
		input_text();
		for (int i = 100; i <= CountOfElem; i*=10)
		{
			SeqTime = Odd_even_sort_sequential(CaseOfArray(Arr100, Arr1000, Arr10000, Arr100000, Arr100000, i),i);
			for (int stream = 2; stream <= 32; stream *= 2)
			{
				Odd_even_sort_parallel_static(CaseOfArray(Arr100, Arr1000, Arr10000, Arr100000, Arr100000,  i), i, stream, SeqTime);
			}
		}
		

		cout << "\n" << "\n";
		cout << "Последовательный алгоритм			dynamic	- Параллельный алгоритм" << endl;
		input_text();
		for (int i = 100; i <= CountOfElem; i *= 10)
		{
			SeqTime = Odd_even_sort_sequential(CaseOfArray(Arr100, Arr1000, Arr10000, Arr100000, Arr100000, i), i);
			for (int stream = 2; stream <= 32; stream *= 2)
			{
				Odd_even_sort_parallel_dynamic(CaseOfArray(Arr100, Arr1000, Arr10000, Arr100000, Arr100000, i), i, stream, SeqTime);
			}
		}
		

		cout << "\n" << "\n";
		cout << "Последовательный алгоритм			guided - Параллельный алгоритм" << endl;
		input_text();
		for (int i = 100; i <= CountOfElem; i *= 10)
		{
			SeqTime = Odd_even_sort_sequential(CaseOfArray(Arr100, Arr1000, Arr10000, Arr100000, Arr100000, i), i);
			for (int stream = 2; stream <= 32; stream *= 2)
			{
				Odd_even_sort_parallel_guided(CaseOfArray(Arr100, Arr1000, Arr10000, Arr100000, Arr100000, i), i, stream, SeqTime);
			}
		}
		
		cout << "\n" << "\n";
		cout << "Последовательный алгоритм			runtime	- Параллельный алгоритм" << endl;
		input_text();
		for (int i = 100; i <= CountOfElem; i *= 10)
		{
			SeqTime = Odd_even_sort_sequential(CaseOfArray(Arr100, Arr1000, Arr10000, Arr100000, Arr100000, i), i);
			for (int stream = 2; stream <= 32; stream *= 2)
			{
				Odd_even_sort_parallel_runtime(CaseOfArray(Arr100, Arr1000, Arr10000, Arr100000, Arr100000, i), i, stream, SeqTime);
			}
		}
		
		cout << "\n" << "\n";
		cout << "Последовательный алгоритм			for - Параллельный алгоритм" << endl;
		input_text();
		for (int i = 100; i <= CountOfElem; i *= 10)
		{
			SeqTime = Odd_even_sort_sequential(CaseOfArray(Arr100, Arr1000, Arr10000, Arr100000, Arr100000, i), i);
			for (int stream = 2; stream <= 32; stream *= 2)
			{
				Odd_even_sort_parallel_for(CaseOfArray(Arr100, Arr1000, Arr10000, Arr100000, Arr100000, i), i, stream, SeqTime);
			}
		}
		
		cout << endl << endl;
}

int main(void)
{
	setlocale(LC_ALL, "Russian");
	AllSort();
	system("pause");
	return 0;
}