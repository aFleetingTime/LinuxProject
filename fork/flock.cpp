#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main(int args, const char *argv[])
{
	if(args != 3)
	{
		cout << "flock <file> <fd>" << endl;
		return -1;
	}
	unsigned int fd = *argv[2] - '0';
	if(fd > 1)
	{
		cout << "fd error" << endl;
		return -1;
	}
	int targetFd = open(argv[1], O_RDWR);
	if(targetFd == -1)
	{
		perror("open file error");
		return -1;
	}
	flock fileLock;
	fileLock.l_type = fd;
	fileLock.l_whence = SEEK_SET;
	fileLock.l_start = 0;
	fileLock.l_len = 0;

	if(fcntl(targetFd, F_SETLKW, &fileLock) == -1)
	{
		perror("lock error");
		return -1;
	}
	cout << "flock - lock" << endl;

	sleep(10);

	fileLock.l_type = F_UNLCK;
	if(fcntl(targetFd, F_SETLKW, &fileLock) == -1)
	{
		perror("unlock error");
		return -1;
	}
	cout << "flock - unlock" << endl;

	close(targetFd);

	return 0;
}
