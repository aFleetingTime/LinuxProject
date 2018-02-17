#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <signal.h>

using namespace std;

void sigusr1Exit(int signo)
{
	exit(0);
}

int main()
{
	if(fork())
	{
		signal(SIGUSR1, sigusr1Exit);
		while(true) sleep(1);
	}
	else
	{
		setsid();
		kill(getppid(), SIGUSR1);
		struct tm *mtime = nullptr;
		time_t utime = 0;
		while(true)
		{
			utime = time(nullptr);
			mtime = localtime(&utime);
			cout << "当前时间:" << mtime->tm_hour << ':' << mtime->tm_min << ':' << mtime->tm_sec << endl;
			sleep(2);
		}
	}
	return 0;
}
