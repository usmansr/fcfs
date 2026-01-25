#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_THREADS 10

void* print_hello(void* arg)
{
    int tid = *(int*)arg;
    printf("Hello, World from thread %d\n", tid);
    return NULL;
}

int main(void)
{
    pthread_t threads[NUMBER_OF_THREADS];
    int thread_ids[NUMBER_OF_THREADS];
    int status;

    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        thread_ids[i] = i;
        printf("Main here, creating thread %d\n", i);

        status = pthread_create(
            &threads[i],
            NULL,
            print_hello,
            &thread_ids[i]
        );

        if (status != 0)
        {
            printf("Error code: %d\n", status);
            exit(EXIT_FAILURE);
        }
    }

    // 🔑 WAIT FOR THREADS
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
