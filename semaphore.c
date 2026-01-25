#include <unistd.h>
 #include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t semaphore;

#define THREAD_NUM 4

void* routine(void* args)
{
	sem_wait(&semaphore);
	{
		sleep(1);
		printf("Hello from thread %d\n", *(int*)args);
	}
	sem_post(&semaphore);
	free(args);
}

int main(int argc, char* argv[])
{
	pthread_t th[THREAD_NUM];
	sem_init(&semaphore, 0, 1);
	int i;
	for(i = 0; i < THREAD_NUM; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if(pthread_create(&th[i], NULL, &routine, a) != 0)
		{
			perror("Failed to create thread");
		}
	}

	// Free resourses
	for(i = 0; i < THREAD_NUM; i++)
	{
		if(pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to Join");
		}
	}

	sem_destroy(&semaphore);
	return 0;
}
