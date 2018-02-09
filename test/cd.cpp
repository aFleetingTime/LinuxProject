#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
		return -1;
	chdir(argv[1]);
	system("pwd");
	return 0;
}
