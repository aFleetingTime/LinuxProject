#include "quickSort.h"
#include "quickSort.cpp"
#include <random>

using namespace std;

constexpr int LEN = 10;
random_device orandom;

void setRandom(int *array, int len)
{
	for(int i = 0; i < len; ++i)
		array[i] = orandom() % static_cast<int>(len * 1.5);
}

void printArray(int *array, int len)
{
	for(int i = 0; i < len; ++i)
		cout << array[i] << ' ';
	cout << endl;
}

int main()
{
	int array[LEN]{};
	setRandom(array, LEN);
	cout << "排序前:";
	printArray(array, LEN);
	quickSort(array, 0, LEN - 1);
	cout << "排序后:";
	printArray(array, LEN);

	return 0;
}

