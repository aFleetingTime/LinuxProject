#include <iostream>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <cstdio>

using namespace std;

int main()
{
	int fd = open("./test.txt", O_RDWR);
	lseek(fd, 0, SEEK_END);
	write(fd, "a", 1);
	struct stat mstat{};
	fstat(fd, &mstat);
	char *mptr = (char *)mmap(nullptr, mstat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(mptr == MAP_FAILED)
	{
		perror("mmap");
		return -1;
	}
	for(int i = 0; i < mstat.st_size; ++i)
		mptr[i] = 'b';
	char buf[1024]{};
	lseek(fd, 0, SEEK_SET);
	read(fd, buf, 1023);
	cout << buf << endl;
	munmap(mptr, mstat.st_size);
	close(fd);
	return 0;
}
