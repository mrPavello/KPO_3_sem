#include <iostream>
#pragma comment(lib, "../Debug/SE_asm011a.lib")


extern "C"
{
	int __stdcall getmax(int*, int);
	int __stdcall getmin(int*, int);
}

int main()
{
	int array[10] = { -50, 5, 23, -1, 100, 9, -4, 22, 9, 0 };
	int max = getmax(array, sizeof(array) / sizeof(int));
	int min = getmin(array, sizeof(array) / sizeof(int));
	std::cout << max << std::endl;
	std::cout << min << std::endl;
	std::cout << "getmax + getmin = " << max + min << std::endl;
}