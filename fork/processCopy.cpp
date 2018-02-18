#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_SIZE 4

using namespace std;

int main(int args, char *argv[])
{
	if(args != 4)
	{
		cout << "copy <oldfile> <newfile> <threadnum>" << endl;
		exit(1);
	}
	else if(access(argv[1], F_OK | R_OK))
	{
		cout << "待拷贝文件不存在!" << endl;
		exit(2);
	}
	istringstream toInt(argv[3]);
	int processNum = 0;
	toInt >> processNum;
	if(processNum <= 0)
	{
		cout << "进程数不能小于1!" << endl;
		exit(3);
	}

	int oldfd = open(argv[1], O_RDONLY);
	struct stat oldInfo{};
	fstat(oldfd, &oldInfo);
	int target = open(argv[2], O_RDWR | O_CREAT, oldInfo.st_mode);
	ftruncate(target, oldInfo.st_size);
	char *moldptr = (char*)mmap(nullptr, oldInfo.st_size, PROT_READ, MAP_SHARED, oldfd, 0);
	char *mnewptr = (char*)mmap(nullptr, oldInfo.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, target, 0);
	//int *mnum = (int*)mmap(nullptr, NUM_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);

	size_t aveSize = oldInfo.st_size / processNum;
	vector<size_t> vSize;
	vSize.resize(processNum);
	int mID = 0;
	for(mID = 0; mID < processNum; ++mID)
	{
		vSize[mID] = aveSize;
		if(mID == processNum - 1)
			vSize[mID] = aveSize + (oldInfo.st_size % processNum);
		if(!fork())
			break;
	}

	if(mID != processNum)
	{
		int len = aveSize * mID;
		strncpy(mnewptr + len, moldptr + len, vSize[mID]);
	}
	else
	{
		while(wait(nullptr) != -1)
			cout.put('=');
		cout << endl;
	}

	munmap(moldptr, oldInfo.st_size);
	munmap(mnewptr, oldInfo.st_size);
	close(oldfd);
	close(target);

	return 0;
}
