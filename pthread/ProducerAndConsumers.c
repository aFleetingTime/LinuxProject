#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

typedef struct foodNode
{
	char *foodName;
	struct foodNode *next;
}Food;
typedef struct foodHead
{
	Food *next;
	size_t foodNum;
}FoodHead;
FoodHead foodHead;
char *name = ".";
pthread_mutex_t mutex;
pthread_cond_t cond;

void *Producer(void *arg)
{
	while(1)
	{
		Food *newFood = (Food*)malloc(sizeof(Food));
		if(newFood == NULL)
			continue;
		newFood->foodName = name;

		pthread_mutex_lock(&mutex);

		newFood->next = foodHead.next;
		foodHead.next = newFood;
		printf("生产者生产%s 物品剩余:%ld\n", newFood->foodName, ++foodHead.foodNum);

		pthread_mutex_unlock(&mutex);

		pthread_cond_signal(&cond);

		sleep(rand() % 3);
	}
	pthread_exit(NULL);
}
void *Consumers(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(!foodHead.foodNum)
			pthread_cond_wait(&cond, &mutex);

		Food *temp = foodHead.next;
		foodHead.next = temp->next;

		printf("消费者购买%s 物品剩余:%ld\n", temp->foodName, --foodHead.foodNum);

		pthread_mutex_unlock(&mutex);

		free(temp);

		sleep(rand() % 3);
	}
	pthread_exit(NULL);
}

int main()
{
	srand((unsigned int)time(NULL));

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);

	pthread_t producer = 0, consumers = 0;

	pthread_create(&producer, NULL, Producer, NULL);
	pthread_create(&consumers, NULL, Consumers, NULL);

	pthread_join(producer, NULL);
	pthread_join(consumers, NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);

	return 0;
}
