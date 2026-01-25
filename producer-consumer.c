#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define THREADS_NUM 2

int buffer[10];
int count = 0;

void* producer(void* p)
{
	int x = rand() % 100;

	buffer[count] = x;
	count++;

}

void* consumer(void* p)
{
	int y = buffer[count - 1];
	count--;
	printf("Got %d from buffer\n", y);

}

int main (void)
{
	srand(time(NULL));
	pthread_t th[THREADS_NUM];
	int i;
	for(i = 0; i < THREADS_NUM; i++)
	{
		if(i % 2 == 0)
		{
			if(pthread_create(&th[i], NULL, &producer, NULL) != 0)
			{
				perror("Failed to create thread");
			}
		} else {
			if(pthread_create(&th[i], NULL, &consumer, NULL) != 0)
                        {
                                perror("Failed to create thread");
                        }
		}

	}

	for (i = 0; i < THREADS_NUM; i++)
	{
		if(pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to Join");
		}
	}
	return 0;

}
