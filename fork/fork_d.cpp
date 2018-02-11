#include <iostream>
#include <unistd.h>
#include <cstdio>

using namespace std;

int main()
{
	int a = fork(), b = printf("run\n");
	if(a)
		printf("parent\n");
	else
		printf("child\n");

	return 0;
}
