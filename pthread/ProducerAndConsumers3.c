#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define ASIZE 5

char *queue[ASIZE];
char *name = "面包";
sem_t psem;
sem_t csem;

void *Producer(void *arg)
{
	int index = 0;
	while(1)
	{
		sem_wait(&psem);

		queue[index] = (char*)malloc(strlen(name) + 1);
		strcpy(queue[index], name);
		printf("生产者生产:%s\n", queue[index++]);
		index %= ASIZE;

		sem_post(&csem);
	}
	pthread_exit(NULL);
}
void *Consumers(void *arg)
{
	int index = 0;
	while(1)
	{
		sem_wait(&csem);

		printf("消费者购买:%s\n", queue[index]);
		free(queue[index]);
		queue[index++] = NULL;
		index %= ASIZE;

		sem_post(&psem);
	}
	pthread_exit(NULL);
}

int main()
{
	sem_init(&psem, 0, 5);
	sem_init(&csem, 0, 0);

	pthread_t producer = 0, consumers = 0;

	pthread_create(&producer, NULL, Producer, NULL);
	pthread_create(&consumers, NULL, Consumers, NULL);

	pthread_join(producer, NULL);
	pthread_join(consumers, NULL);

	sem_destroy(&psem);
	sem_destroy(&csem);

	return 0;
}
