#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>

#define READ_THREAD_SIZE 5
#define WRITE_THREAD_SIZE 3

using namespace std;

pthread_rwlock_t rwlock{};
int num = 0;

void *readDate(void *arg)
{
	while(true)
	{
		pthread_rwlock_rdlock(&rwlock);
		printf(" Read:%d\n", num);
		pthread_rwlock_unlock(&rwlock);
		usleep(1500);
	}
	pthread_exit(nullptr);
}

void *writeDate(void *arg)
{
	while(true)
	{
		pthread_rwlock_wrlock(&rwlock);
		cout << "Write:" << num << " - " << ++num << endl;
		pthread_rwlock_unlock(&rwlock);
		usleep(1500);
	}
	pthread_exit(nullptr);
}

int main()
{
	pthread_t tps[8]{};
	int tnum = 0;

	pthread_rwlock_init(&rwlock, nullptr);

	for(int i = 0; i < READ_THREAD_SIZE; ++i)
		pthread_create(&tps[tnum++], nullptr, readDate, nullptr);
	for(int i = 0; i < WRITE_THREAD_SIZE; ++i)
		pthread_create(&tps[tnum++], nullptr, writeDate, nullptr);

	for(int i = 0; i < tnum; ++i)
		pthread_join(tps[i], nullptr);

	pthread_rwlock_destroy(&rwlock);

	pthread_exit(nullptr);
}
