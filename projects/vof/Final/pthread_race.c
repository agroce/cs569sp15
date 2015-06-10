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
    ++g;
    printf("%i Global: %d\n", i, g);
}
 
void *myCheckFun(void *vargp)
{
    int i = (int)vargp;
    ++g;
    printf("%i Global: %d\n", i, g);
    if(g != 4){
        ERROR: goto ERROR;
        ;
    }
}

int threadCount(int num_threads)
{
    int i;
    pthread_t tid;
    pthread_t threads[num_threads];
 
    // Let us create threads
    for (i = 0; i < num_threads-1; i++)
        pthread_create(&threads[i], NULL, myThreadFun, (void *)i);
    
    // pthread_create(&threads[num_threads-1], NULL, myCheckFun, (void *)num_threads-1);
    
    for (i = 0; i < num_threads; i++)
    	pthread_join(threads[i],NULL);

    // printf("Global: %d\n", g);
    // assert (g >= 0);
    // assert (g <= num_threads);
    return g; 
}

int main(int argc, char const *argv[])
{
    int result = threadCount(4);

    assert(result == 4);
    // if(result == 4){
    //     ERROR: goto ERROR;
    //     ;
    // }
    return 0;
}