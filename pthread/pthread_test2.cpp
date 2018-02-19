#include <iostream>
#include <array>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_COUNT 10000

using namespace std;

int num = 0;
pthread_mutex_t mutex{};
bool mylock = false;

void fun(const bool &mylock)
{
	while(mylock);
}
void mylock_fun(bool &mylock)
{
	fun(mylock);
	mylock = true;
}
void *addNum_lock(void *arg)
{
	for(int i = 0; i < MAX_COUNT; ++i)
	{
		pthread_mutex_lock(&mutex);
		mylock_fun(mylock);
		pthread_mutex_unlock(&mutex);
		int temp = num;
		temp++;
		num = temp;
		cout << "num:" << num << endl;
		mylock = false;
		usleep(1);
	}
	pthread_exit(nullptr);
}

int main()
{
	pthread_mutex_init(&mutex, nullptr);

	array<pthread_t, 2> pts{};
	pthread_create(&pts[0], nullptr, addNum_lock, nullptr);
	pthread_create(&pts[1], nullptr, addNum_lock, nullptr);

	for(int i = 0; i < 2; ++i)
		pthread_join(pts[i], nullptr);
	pthread_exit(nullptr);
}
