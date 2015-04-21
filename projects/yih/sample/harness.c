//#include <stdio.h>
#include "sort.h"

int a[SIZE];
int nondet_int(); //function that returns an arbitrary integer value.
unsigned int nondet_unsigned_int(); //function that returns an arbitrary unsigned integer value.

int main()
{
	int i, v, last, val;
	int refc = 0;
	int acount = 0;
	unsigned int s = nondet_unsigned_int(); //s is an arbitrary unsigned_int
	__CPROVER_assume(s <= SIZE); // s is used to loop for a[],so assume s<=SIZE
	int val = nondet_int(); //val is an arbitrary int
	printf("LOG: s = %u, val = %d\n", s, val);

	for (i = 0; i < s; i++)
	{   
		v = nondet_int(); //v is an arbitrary int
		a[i] = v; 
		printf("LOG: a[%d] = %d\n", i, v);
		if (v == val)
		{
			refc++; // record times that a[i] has the same value = val
		}
	}

	mysort(a, s); //do sort
	printf("LOG: sorted a\n");

	//after sort, verify two things: 1. whether sorted  2. whether times of values = val keep the same
	
	//1. think about a[0] 
	if (s > 0)
	{
		last = a[0]; //set first tail for comparison
		if (a[0] == val)
		{
			acount++; // record times that a[i] has the same value = val
		}
	}

	//2. think about common a[i]
	for (i = 1; i < s; i++)
	{
		printf("LOG: last = %d, a[%d] = %d\n", last, i, a[i]);
		assert(a[i] >= last); //1. assert whether head is always bigger than tail
		if (a[i] == val)
		{
			acount++; // keep recording times that a[i] has the same value = val
		}
		last = a[i]; // keep updating the tail
	}

	printf("LOG: refc = %d, acount = %d\n", refc, acount);
	assert(refc == acount); //2. assert the number of same value is the same.
}
