#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <signal.h>

using namespace std;

void sigintCase(int signo)
{
	cout << "catch signal:" << signo << endl;
}

int main()
{
	signal(SIGALRM, sigintCase);
	itimerval timeval{ 1, 9, 1, 9 };
	setitimer(ITIMER_REAL, &timeval, nullptr);
	while(true)
	{
		cout << "Programs are running..." << endl;
		sleep(1);
	}
	
	return 0;
}
