#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <array>

using namespace std;

int main()
{
	int fd = open("./test.p", O_WRONLY);
	if(fd == -1)
	{
		perror("write open");
		return -1;
	}
	write(fd, "fifo test ......", 16);
	close(fd);
	return 0;
}
