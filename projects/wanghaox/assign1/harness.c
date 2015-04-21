#include <stdio.h>
#include "heapsort.h"
#include "assert.h"

int array[SIZE];

int nondet_int();
unsigned int nondet_unsigned_int();

int main()
{
	int i, num, last;
	int parent;
	printf("LOG: SIZE = %d\n", SIZE);

	unsigned int size = nondet_unsigned_int();
	__CPROVER_assume (size <= SIZE);
	printf("LOG: size = %u", size);

	for (i = 0; i < size; i++)
	{
		num = nondet_int();
		array[i] = num;
		printf("LOG: array[%d] = %d\n", i, num);
	}

	makeheap(array, size);
	printf("LOG: Create heap\n");
	//check if the heap is correct
	for (i = 1; i < size; i++)
	{
		parent = array[(i - 1) / 2];
		printf("LOG: parent(array[%d] = %d, array[%d] = %d\n", (i - 1) / 2, parent, i, array[i]);
		assert(parent >= array[i]);
	}

	heapsort(array, size);
	printf("LOG: Sorted array.\n");

	//check if the heap sorted
	if (size> 0)
	{
		last = array[0];
	}
	for (i = 1; i < size; i++)
	{
		printf("LOG: last = %d, array[%d] = %d\n", last, i, array[i]);
		assert(array[i] >= last);
		last = array[i];
	}
	return 0;
}
