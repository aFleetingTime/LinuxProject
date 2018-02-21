#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

typedef struct philosopher
{
	pthread_t mTID;
	char name;
	pthread_mutex_t chopstick;
}Philosopher;

typedef struct philosopherInfo
{
	size_t phiTotal;
	int pNum;
	int isLast;
}PhilosopherInfo;

#define NUM 5

Philosopher pInfo[NUM];
pthread_mutex_t mutex;
size_t gtotal = 0;
int noodle = 1000;

void philosopher_array_init(Philosopher *pArray, size_t len)
{
	for(int i = 0; i < len; ++i)
	{
		pArray[i].mTID = 0;
		pArray[i].name = 'A' + i;
		pthread_mutex_init(&pArray[i].chopstick, NULL);
	}
}

void *repast(void *arg)
{
	int *num = (int*)malloc(sizeof(int));
	PhilosopherInfo *pi = (PhilosopherInfo*)arg;
	int max = noodle;
	while(noodle-- > 0)
	{
		pthread_mutex_lock(&mutex);
		if(pi->pNum % 2 == 1)
		{
			pthread_mutex_lock(&pInfo[pi->pNum].chopstick);
			if(noodle <= 0 || pthread_mutex_trylock(&pInfo[(pi->pNum + 1) % pi->phiTotal].chopstick))
			{
				pthread_mutex_unlock(&pInfo[pi->pNum].chopstick);
				pthread_mutex_unlock(&mutex);
				++noodle;
				continue;
			}
		}
		else
		{
			pthread_mutex_lock(&pInfo[(pi->pNum + 1) % pi->phiTotal].chopstick);
			if(noodle <= 0 || pthread_mutex_trylock(&pInfo[pi->pNum].chopstick))
			{
				pthread_mutex_unlock(&pInfo[(pi->pNum + 1) % pi->phiTotal].chopstick);
				pthread_mutex_unlock(&mutex);
				++noodle;
				continue;
			}
		}
		++*num;
		++gtotal;
		pthread_mutex_unlock(&mutex);
		//printf("%d, %ld\n", noodle, gtotal);
		pthread_mutex_unlock(&pInfo[pi->pNum].chopstick);
		pthread_mutex_unlock(&pInfo[(pi->pNum + 1) % pi->phiTotal].chopstick);
	}
	pthread_exit(num);
}

int main()
{
	pthread_mutex_init(&mutex, NULL);
	philosopher_array_init(pInfo, sizeof(pInfo) / sizeof(*pInfo));
	for(int i = 0; i < NUM; ++i)
	{
		PhilosopherInfo *temp = (PhilosopherInfo*)malloc(sizeof(PhilosopherInfo));
		temp->phiTotal = NUM;
		temp->pNum = i;
		temp->isLast = (i == NUM - 1) ? 1 : 0;
		pthread_create(&pInfo[i].mTID, NULL, repast, (void*)temp);
	}
	int *num = NULL;
	for(int i = 0; i < NUM; ++i)
	{
		pthread_join(pInfo[i].mTID, (void**)&num);
		if(!i)
			printf("--------------------\n统计结果:\n");
		printf("哲学家%c吃到了%d根面条\n", pInfo[i].name, *num);
		free(num);
	}
	printf("共计:%ld\n剩余:%d\n", gtotal, noodle);

	for(int i = 0; i < NUM; ++i)
		pthread_mutex_destroy(&pInfo[i].chopstick);
	pthread_mutex_destroy(&mutex);

	return 0;
}
