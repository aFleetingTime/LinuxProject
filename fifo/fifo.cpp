#include <iostream>
#include <string>
#include <array>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main()
{
	//int mode = getumask();
	if(mkfifo("./temp", 0664) == -1)
	{
		perror("make fifo");
		return -1;
	}
	int fd = open("./temp", O_RDWR);
	unlink("./temp");
	switch(fork())
	{
	case -1:
		perror("fork");
		return 0;
	case 0:
		write(fd, "fifo function test file", 2323);
		break;
	default:
		array<char, 512> buf{};
		read(fd, buf.data(), buf.size());
		cout << buf.data() << endl;
		break;
	}
	close(fd);
	return 0;
}
