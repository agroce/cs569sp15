#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
 
// Let us create a global variable to change it in threads
int g = 0;

pthread_mutex_t mutexsum;

// The function to be executed by all threads
void *myThreadFun(void *vargp)
{
    int i = (int)vargp;
    pthread_mutex_lock (&mutexsum);
    printf("%i Global: %d\n", i, ++g);
    pthread_mutex_unlock (&mutexsum);
}
 
int threadCount(int num_threads)
{
    int i;
    pthread_t tid;
    pthread_t threads[num_threads];
    pthread_attr_t attr;
 
    pthread_mutex_init(&mutexsum, NULL);
         
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Let us create threads
    for (i = 0; i < num_threads; i++)
        pthread_create(&threads[i], &attr, myThreadFun, (void *)i);
    
    pthread_attr_destroy(&attr);

    for (i = 0; i < num_threads; i++)
    	pthread_join(threads[i],NULL);

    // printf("Global: %d\n", g);
    // assert (g == num_threads);
    pthread_mutex_destroy(&mutexsum);
    return g; 
    pthread_exit(NULL);
}