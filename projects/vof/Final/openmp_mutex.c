#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
 
// Let us create a global variable to change it in threads
int g = 0;
 
int threadCount(int num_threads)
{

    int i;
    #pragma omp parallel for
    for (i = 0; i < num_threads; ++i)
    {
        #pragma omp critical
        printf("%i Global: %d\n", i, ++g);
    }


    return g;
}