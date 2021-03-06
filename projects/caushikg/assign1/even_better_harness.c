#include <stdio.h>
#include <assert.h>
#include "priority_queue.h"

unsigned int nondet_unsigned_int();

int check_queue(unsigned int a[], unsigned int copy[], int size);
void sort_copy(unsigned int copy[], int size);


// Check if the array is sorted by priority, because that is how the insert_by_priority function
// should work, it adds according to priority, higher priority is the front of the queue, the lowest
// is the rear of the queue.
int check_queue(unsigned int a[], unsigned int copy[], int size) 
{
	int i;
	int num_items = (rear - front) + 1;

	if(num_items != size)
		return -1;

	sort_copy(copy, size);

	/* LOGGING CODE

	printf("LOG: COPY = ");
	for (i=0; i<size; i++) {
		printf("LOG: %d ", copy[i]);
	}
	printf("\nLOG: REAL = ");
	for (i=0; i<size; i++) {
		printf("LOG: %d ", a[i]);
	}
	*/	

	for (i=0; i<size; i++) {

		if (a[i] != copy[i])
			return -1;
	
		if (i == size-1) 
			break;
	
		else {
			if (a[i] < a[i+1])
				return -1;
		}
	}

	return 0;	

}


void sort_copy(unsigned int copy[], int size) 
{

	int i, j;
	unsigned int temp;
  	
	for (i = 0; i < size; i++) {
    		for (j = i; j < size; j++) {
      			if (copy[i] < copy[j]) {
				temp = copy[i];
				copy[i] = copy[j];
				copy[j] = temp;
      			}
    		}
  	}


}


int main()
{

	int i, asize, check;
	unsigned int item;

	unsigned int copy[MAX];

        create();

	asize = 0;

	unsigned int s = nondet_unsigned_int();
  	__CPROVER_assume (s <= MAX);

	for (i=0; i<s; i++) {
		item = nondet_unsigned_int();
		insert_by_priority(item);
		asize++;
		display_pqueue();
		check = check_queue(pri_que, copy, asize);
		assert(check == 0);
	}
			
        return 0;

}
