#include <stdio.h>
#include <assert.h>
#include "priority_queue.h"

unsigned int nondet_unsigned_int();
int nondet_int();

int check_queue(unsigned int a[], int size);


// Check if the array is sorted by priority, because that is how the insert_by_priority function
// should work, it adds according to priority, higher priority is the rear of the queue, the lowest
// is the front of the queue.
// Same thing with delete_by_priority, it should delete the item in the queue with the highest 
// priority, still leaving the queue sorted by priority.
int check_queue(unsigned int a[], int size) 
{
	int i;
	for (i=0; i<size; i++) {
		if (i == size-1) 
			break;	
		else {
			if (pri_que[i] > pri_que[i+1])
				return -1;
		}
	}

	return 0;	

}


int main()
{

	int i, asize, check, iterations;
	unsigned int item;
	int choice;

        create();

	asize = 0;

	
	while ((iterations <= MAX_ITER) && (asize <= MAX)) {
		choice = nondet_int();

		__CPROVER_assume ((choice == 1) || (choice == 2));

		if (choice == 1) {
			item = nondet_unsigned_int();
			insert_by_priority(item);
			asize++;
		}

		else {
			delete_by_priority();
			asize--;
		}

		check = check_queue(pri_que, asize);
		assert(check == 0);
	}
		
		
        return 0;

}
