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
	sleep(5);
	cout << "sigintCase Over" << endl;
}

int main()
{
	struct sigaction actionVal{};
	actionVal.sa_handler = sigintCase;
	sigemptyset(&actionVal.sa_mask);
	//sigaddset(&actionVal.sa_mask, SIGINT);
	actionVal.sa_flags = 0;
	sigaction(SIGALRM, &actionVal, nullptr);
	//sigemptyset(&actionVal.sa_mask);
	sigaction(SIGINT, &actionVal, nullptr);

	itimerval timeval{ 1, 9, 1, 9 };
	setitimer(ITIMER_REAL, &timeval, nullptr);

	while(true)
	{
		cout << "Programs are running..." << endl;
		sleep(1);
	}
	
	return 0;
}
