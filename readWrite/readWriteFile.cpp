#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

using namespace std;

constexpr int maxSize = 512;

int main()
{
	int fd = open("./text.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
	printf("fd = %d\n", fd);
	if(fd == -1)
	{
		perror("open");
		return fd;
	}

	char buf[maxSize] = "is test file...\n";
	int ret = 0;

	ret = write(fd, buf, strlen(buf));
	if(ret == -1)
	{
		perror("write");
		return ret;
	}

	buf[0] = '\0';

	lseek(fd, 0, SEEK_SET);
	ret = read(fd, buf, maxSize);
	if(ret == -1)
	{
		perror("read");
		return ret;
	}
	printf("%s", buf);

	ret = close(fd);
	if(ret == -1)
	{
		perror("close");
		return ret;
	}

	return 0;
}

