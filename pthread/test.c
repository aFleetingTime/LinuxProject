#include <stdio.h>

void fun(int *restrict a, int *restrict b)
{
	*a = 1000;
	*b = 10000;
	int *p = a;
	*p = 100000;
	printf("a = %d\n", *a);
	printf("b = %d\n", *b);
}

int main()
{
	int i = 10;
	int *a = &i;
	fun(&i, &i);
	printf("main a = %d\n", *a);
	printf("main i = %d\n", i);

	return 0;
}
