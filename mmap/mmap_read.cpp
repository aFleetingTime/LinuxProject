#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main()
{
	string path("./rdwr.txt");
	int fd = 0;
	if(access(path.c_str(), F_OK))
	{
		fd = open(path.c_str(), O_RDWR | O_CREAT, 0664);
		ftruncate(fd, 4096);
	}
	else
		fd = open(path.c_str(), O_RDWR);
	if(fd == -1)
	{
		perror("open file error");
		return -1;
	}

	struct stat mstat{};
	if(fstat(fd, &mstat))
	{
		perror("stat file error");
		return -1;
	}

	char *start = (char *)mmap(nullptr, mstat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(start == MAP_FAILED)
	{
		perror("mmap file error");
		return -1;
	}

	while(*start == 0);
	cout << "read:" << start << endl;
	*start = EOF;

	if(munmap(start, 4096))
	{
		perror("munmap error");
		return -1;
	}
	close(fd);
	
	return 0;	
}
