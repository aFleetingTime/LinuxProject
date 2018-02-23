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
	a[0] = "grep";
	a[1] = "a";
	dup2(4, 0);
	if(!vfork())
	{
		execvp("grep", a);
		perror("vfork");
	}
	return 0;
}
