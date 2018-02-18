#include <iostream>
#include <array>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_COUNT 10000

using namespace std;

int num = 0;
pthread_mutex_t mymutex{};

void *addNum_lock(void *arg)
{
	for(int i = 0; i < MAX_COUNT; ++i)
	{
		pthread_mutex_lock(&mymutex);
		int temp = num;
		temp++;
		num = temp;
		cout << "num:" << num << endl;
		pthread_mutex_unlock(&mymutex);
		usleep(1);
	}
	pthread_exit(nullptr);
}
void *addNum_trylock(void *arg)
{
	for(int i = 0; i < MAX_COUNT; ++i)
	{
		while(pthread_mutex_trylock(&mymutex));
		int temp = num;
		temp++;
		num = temp;
		cout << "num:" << num << endl;
		pthread_mutex_unlock(&mymutex);
		usleep(1);
	}
	pthread_exit(nullptr);
}

int main()
{
	pthread_mutex_init(&mymutex, nullptr);

	array<pthread_t, 2> pts{};
	pthread_create(&pts[0], nullptr, addNum_lock, nullptr);
	pthread_create(&pts[1], nullptr, addNum_trylock, nullptr);

	for(int i = 0; i < pts.size(); ++i)
		pthread_join(pts[i], nullptr);

	pthread_mutex_destroy(&mymutex);
	pthread_exit(nullptr);
}
