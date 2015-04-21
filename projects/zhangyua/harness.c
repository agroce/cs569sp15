#include <stdio.h>
#include "primes.h"

int a[SIZE];

int nondet_int();
unsigned int nondet_unsigned_int();

int main(int argc, char const *argv[])
{
	int i, n, j;
	int pnum = 0;
	unsigned int s = nondet_unsigned_int();
	__CPROVER_assume (s <= SIZE);
	n = primes(a, SIZE);
	for(i = 0; i < n; i ++) {
		for(j = 3; j < a[n]; j ++) {
			if (a[i] % j != 0) {
				pnum += 1;
			}
		}
	}
	assert (pnum == n);
	return 0;
}

