#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* kidFunc(void* p)
{
	pthread_t* ptr = (pthread_t *)p;
	printf("Kid thread id: %p\n", ptr);
}

int main(void)
{
	pthread_t kid;
	pthread_create(&kid, NULL, kidFunc, (void *)&kid);
	pthread_join(kid, NULL);
	return 0;
}
