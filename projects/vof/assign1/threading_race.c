#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
 
// Let us create a global variable to change it in threads
int g = 0;
 
// The function to be executed by all threads
void *myThreadFun(void *vargp)
{
    int i = (int)vargp;
    printf("%i Global: %d\n", i, ++g);
}
 
int threadCount(int num_threads)
{
    int i;
    pthread_t tid;
    pthread_t threads[num_threads];
 
    // Let us create threads
    for (i = 0; i < num_threads; i++)
        pthread_create(&threads[i], NULL, myThreadFun, (void *)i);
    
    for (i = 0; i < num_threads; i++)
    	pthread_join(threads[i],NULL);

    // printf("Global: %d\n", g);
    // assert (g >= 0);
    // assert (g <= num_threads);
    return g; 
}