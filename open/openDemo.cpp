#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>

constexpr int maxSize = 512;

int main()
{
	int fd = open("./text.txt", O_RDONLY);
	printf("fd = %d\n", fd);
	if(fd == -1)
	{
		perror("open");
		return fd;
	}

	char buf[maxSize];
	read(fd, buf, maxSize);
	perror("read:");
	printf("%s", buf);

	int ret = close(fd);
	if(ret == -1)
	{
		perror("close");
		return ret;
	}

	return 0;
}

