#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd = open("text.txt", O_WRONLY);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}
	int size = lseek(fd, 1000, SEEK_END);
	printf("file size:%d\n", size);
	write(fd, "a", 1);
	size = lseek(fd, -1002, SEEK_END);
	printf("-1002:%d\n", size);
	write(fd, "a", 1);
	close(fd);
	return 0;
}
