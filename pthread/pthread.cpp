#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

using namespace std;

void *func(void *arg)
{
	cout << "child thread:" << pthread_self() << endl;
	return nullptr;
}

int main()
{
	pthread_t ctp = 0;
	pthread_create(&ctp, nullptr, func, nullptr);
	sleep(1);
	cout << "main thread:" << pthread_self() << endl;
	return 0;
}
