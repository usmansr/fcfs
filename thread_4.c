#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct KidStruct
{
	int id;
	char* name;
};

void* kidFunc(void* p)
{
	printf("I am thread\n");

	struct KidStruct* ptr = (struct KidStruct *) p;
	printf("Printing Structure:\nID: %d\nName: %s\n", ptr->id, ptr->name);
	return NULL;
}

int main(void)
{
	struct KidStruct K;
	K.id = 10;
	K.name = "Ahmad";

	pthread_t kid;
	if (pthread_create(&kid, NULL, kidFunc, &K) != 0)
	{
    		perror("pthread_create failed");
    		return 1;
	}

	pthread_join(kid, NULL);

	return 0;
}
