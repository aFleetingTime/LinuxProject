#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

using namespace std;

void *threadFunc(void *arg)
{
	cout << "child thread" << endl;
	pthread_exit(nullptr);
}

int main()
{
	pthread_attr_t threadAttr{};
	pthread_attr_init(&threadAttr);
	pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);
	pthread_t ctp = 0;
	pthread_create(&ctp, &threadAttr, threadFunc, nullptr);

	usleep(500);
	cout << "main thread" << endl;

	pthread_attr_destroy(&threadAttr);
	pthread_exit(nullptr);
}
