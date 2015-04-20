#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
 
// Let us create a global variable to change it in threads
int g = 0;

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

// The function to be executed by all threads
void *myThreadFun1(void *vargp)
{
    int i = (int)vargp;
    pthread_mutex_lock (&mutex1);
    pthread_mutex_lock (&mutex2);
    printf("1 Global: %d\n", ++g);
    pthread_mutex_lock (&mutex2);
    pthread_mutex_unlock (&mutex1);
}

void *myThreadFun2(void *vargp)
{
    int i = (int)vargp;
    pthread_mutex_lock (&mutex1);
    pthread_mutex_lock (&mutex2);
    printf("2 Global: %d\n", ++g);
    pthread_mutex_unlock (&mutex2);
    pthread_mutex_lock (&mutex1);
}

int threadCount(int num_threads)
{
    int i;
    pthread_t tid;
    pthread_t threads[2];
    pthread_attr_t attr;
 
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
         
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Let us create threads
    i = 0;
    pthread_create(&threads[0], &attr, myThreadFun1, (void *)i);
    pthread_create(&threads[1], &attr, myThreadFun2, (void *)i);
    
    pthread_attr_destroy(&attr);

    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);

    // printf("Global: %d\n", g);
    // assert (g == num_threads);
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
    return g; 
    pthread_exit(NULL);
}