#include "quickSort.h"

template<class T>
void quickSort(T *array, const int left, const int right)
{
	if(left >= right)
		return;
	int i = left, j = right;
	T key = array[i];
	while(i < j)
	{
		while(i < j && array[j] >= key)
			--j;
		array[i] = array[j];
		while(i < j && array[i] <= key)
			++i;
		array[j] = array[i];
	}
	array[i] = key;
	quickSort(array, left, i - 1);
	quickSort(array, j + 1, right);
}
