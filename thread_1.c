#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int GLOB_DATA = 5;

void* kidFunc(void *p)
{
	printf("Kid global data: %d\n", GLOB_DATA);
	GLOB_DATA = 100;
	printf("Kid global data: %d\n", GLOB_DATA);
	pthread_exit(NULL);
}


int main(void)
{
	pthread_t kid;
	pthread_create(&kid, NULL, kidFunc, NULL);

	printf("Parent global data: %d\n", GLOB_DATA);
	GLOB_DATA = 10;
	printf("Parent global data: %d\n", GLOB_DATA);

	pthread_join(kid, NULL);

	return 0;
}
