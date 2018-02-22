#include <iostream>
#include <string>
#include <exception>
#include <cstdio>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

void fun(time_t time)
{
	sleep(time);
}

void run(int fd, flock *fileLock, time_t time)
{
	if(fcntl(fd, F_SETLKW, fileLock) == -1)
		throw new ios_base::failure("lock error");
	cout << "flock - lock" << endl;

	fun(time);

	fileLock->l_type = F_UNLCK;
	if(fcntl(fd, F_SETLKW, fileLock) == -1)
		throw new ios_base::failure("unlock error");
	cout << "flock - unlock" << endl;
}

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

	time_t sleepTime = 5;
	try
	{
		if(fork())
		{
			run(targetFd, &fileLock, sleepTime);
			while(wait(nullptr) != -1);
		}
		else
		{
			run(targetFd, &fileLock, sleepTime);
		}
	}
	catch(exception *exc)
	{
		perror(exc->what());
		close(targetFd);
		delete exc;
		return -1;
	}
	close(targetFd);

	return 0;
}
