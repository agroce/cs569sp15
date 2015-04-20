#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include "thread.h"

int main(int argc, char const *argv[])
{
	int result = threadCount(NUM);

	assert(result == NUM);
	return 0;
}






