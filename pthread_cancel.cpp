#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

using namespace std;

void showRun(int signo)
{
	cout << "thread run..." << endl;
}

void *threadFunc(void *arg)
{
	struct sigaction siga{};
	siga.sa_handler = showRun;
	siga.sa_flags = 0;
	//sigaction(SIGALRM, &siga, nullptr);
	sigaction(SIGVTALRM, &siga, nullptr);
	
	itimerval timeVal{ 1, 0, 1, 0 };
	//setitimer(ITIMER_REAL, &timeVal, nullptr);
	setitimer(ITIMER_VIRTUAL, &timeVal, nullptr);

	while(true);

	pthread_exit(nullptr);
}

int main()
{
	pthread_t ctp = 0;
	pthread_create(&ctp, nullptr, threadFunc, nullptr);

	sleep(5);
	pthread_cancel(ctp);

	pthread_exit(nullptr);
}
