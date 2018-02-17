#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <signal.h>

using namespace std;

string homePath(getenv("HOME"));
ofstream ofs(homePath + "/time.txt", ios::out | ios::app);

void sigusr1Exit(int signo)
{
	exit(0);
}
void writeTime(int signo)
{
	time_t utime = 0;
	utime = time(nullptr);
	struct tm *mtime = localtime(&utime);
	char *stime = asctime(mtime);
	ofs << stime;
	ofs.flush();
}

int main()
{
	if(fork())
	  exit(0);

	setsid();
	chdir(homePath.c_str());
	umask(0);
	for(int i = 0; i < 3; ++i)
	  close(i);
	struct sigaction sc{};
	sc.sa_handler = writeTime;
	sc.sa_flags = 0;
	sigaction(SIGALRM, &sc, nullptr);
	itimerval tval{ 2, 0, 2, 0 };
	setitimer(ITIMER_REAL, &tval, nullptr);
	while(true);
	ofs.close();
	return 0;
}
