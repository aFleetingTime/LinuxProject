#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main(int args, char *argv[])
{
	if(args != 2)
	{
		cout << "mmap_write <data>" << endl;
		return -1;
	}
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
	sprintf(start, "%s", argv[1]);

	while(*start != EOF);
	cout << "数据已被其他进程接收" << endl;

	if(munmap(start, mstat.st_size))
	{
		perror("munmap error");
		return -1;
	}
	close(fd);
	unlink(path.c_str());

	return 0;
}
