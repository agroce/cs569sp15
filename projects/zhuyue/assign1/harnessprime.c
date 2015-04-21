#include <stdio.h>
#include "prime.h"

int nondet_int();
unsigned int nondet_unsigned_int();
int SIZE=10;

int main()
{
	int k;
	int e = nondet_int();
	int b;

	__CPROVER_assume(e >= 2 && e <= SIZE);
	
	b = maxprime(e);
	
	assert(b <= e);
	assert(prime(b));
	for (int k = b + 1; k <= e; k++)
	{
		assert(prime(k) == 0);
	}

}