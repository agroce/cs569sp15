#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include "thread.h"

int main(int argc, char const *argv[])
{
	int result = threadCount(4);

	assert(result == 4);
	return 0;
}






