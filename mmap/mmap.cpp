#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>

using namespace std;

int main()
{
	int fd = open("./text.txt", O_RDWR);
	struct stat statBuf;
	if(fstat(fd, &statBuf))
	{
		perror("stat");
		return -1;
	}
	char *map = static_cast<char*>(mmap(nullptr, statBuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
	if(map == MAP_FAILED)
	{
		perror("mmap");
		return -1;
	}

	cout << "file:" << map << endl;
	for(int i = 0; i < statBuf.st_size; ++i)
		map[i] = 'a';
	cout << "new file:" << map << endl;

	if(munmap(map, statBuf.st_size) == -1)
	{
		perror("munmap");
		return -1;
	}
	close(fd);

	return 0;
}
