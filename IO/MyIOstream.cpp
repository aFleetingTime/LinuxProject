#include "MyIOstream.h"

class MyIOstream
{
public:
	MyIOstream()
	{
		mFd = -1;
		mFlag = false;
	}
	int openFile(char *filepath, int flag) {
		if(mFlag)
			return -1;
		mFd = open(filepath, flag);
		if(mFd == -1)
			return -1;
		mFlag = true;
		return 0;
	}
	int openFile(char *filepath, int flag, mode_t mode) {
		if(mFlag)
			return -1;
		mFd = open(filepath, flag, mode);
		if(mFd == -1)
			return -1;
		mFlag = true;
		return 0;
	}
	int readFile(char *buf, size_t bufSize)
	{
		return read(mFd, buf, bufSize);
	}
	int writeFile(char *buf, size_t bufSize)
	{
		return write(mFd, buf, bufSize);
	}
	int close()
	{
		if(mFd != -1)
			return ::close(mFd);
		return -1;
	}
	~MyIOstream()
	{
		if(mFd != -1)
			::close(mFd);
	}

private:
	int mFd;
	bool mFlag;
};
