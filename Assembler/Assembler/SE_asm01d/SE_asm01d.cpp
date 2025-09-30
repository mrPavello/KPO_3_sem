#include <iostream>
#include "Windows.h"

using namespace std;

extern "C"
{
	int  getmax(int* arr,int size)
	{
		if (size == 0) throw new exception();
		
		int max = INT_MIN;
		for (size_t i = 0; i < size; i++)
		{
			if (arr[i] > max)
			{
				max = arr[i];
			}
		}

		return max;
	}

	int  getmin(int* arr, int size)
	{
		if (size == 0) throw new exception();

		int min = INT_MAX;
		for (size_t i = 0; i < size; i++)
		{
			if (arr[i] < min)
			{
				min = arr[i];
			}
		}

		return min;
	}

	void Print(int num)
	{
		cout << num << endl;
	}

	void Console1251()
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
	}

	void PrintResult(int max,int min)
	{
		cout << "getmax + getmin = " << max + min << endl;
	}

}