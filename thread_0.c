#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* childFunc(void* p)
{
	printf("I am a child thread, Process id: %d\n", getpid());
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t child;

	pthread_create (&child, NULL, childFunc, NULL);

	printf("I am parent and my process id: %d\n", getpid());
	pthread_join(child, NULL);

	printf("No more threads!\n");

	return 0;
}
