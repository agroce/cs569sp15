#include <stdio.h> 
#include "assert.h"
#include "prime.h"
#include "time.h"
int array[SIZE];


int nondet_int();
unsigned int nondet_unsigned_int();

void main()
{	
	int i,first;
	unsigned int initial_no = nondet_int();
	unsigned int size = nondet_int();
	__CPROVER_assume (size <= SIZE); 
	jsValue(initial_no,size,array);
	first = array[0];
	for(i=1;i<size;i++)
	{		
		assert( array[i]<=first);
		first=array[i];
	}

}
