#pragma once
#include <sys/types.h>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;



class MyIOstreama
{
public:
    int openFile(char *filepath, int flag);
    int openFile(char *filepath, int flag, mode_t mode);
	int readFile(char *buf, size_t bufSize);
	int writeFile(char *buf, size_t bufSize);
	int close();

private:
	int mFd;
	bool mFlag;
};
