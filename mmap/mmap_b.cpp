#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <cstdio>

using namespace std;

int main()
{
	char *mptr = (char *)mmap(nullptr, 4096, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
	if(mptr == MAP_FAILED)
	{
		perror("mmap");
		return -1;
	}
	if(fork())
	{
		for(int i = 0; i < 10; ++i)
			mptr[i] = 'b';
	}
	else
	{
		cout << mptr << endl;
	}
	if(munmap(mptr, 4096))
	{
		perror("munmap");
		return 0;
	}
	return 0;
}
