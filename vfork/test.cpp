#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main()
{
	char *a[5]{};
	a[0] = "ls";
	if(!vfork())
	{
		execvp("ls", a);
		perror("vfork");
	}
	return 0;
}
