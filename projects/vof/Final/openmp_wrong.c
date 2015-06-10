#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
 
// Let us create a global variable to change it in threads
int g = 0;
 
int threadCount(int num_threads)
{
    // Let us create threads
    int i;
    for (i = 0; i < num_threads; ++i)
    {
        printf("%i Global: %d\n", i, ++g);
    }

    return g;
}