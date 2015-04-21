#include <stdio.h>
#include "mybinsearch.h"
#include <assert.h>



int nondet_int();
unsigned int nondet_unsigned_int();

int a[SIZE];

int main()
{

	int k, m, n, i, j, p;

	printf("LOG: SIZE = %d\n", SIZE);
	n = nondet_unsigned_int();
	__CPROVER_assume((0<=n) && (n<SIZE));
	printf("LOG: n = %d\n", n);
//bug introduced on-purpose by giving random 'n'; Exceed the array size


	p = nondet_int();
	__CPROVER_assume((p<0) || (p>20/*SIZE*/)); //Bug Introduced while ranging p>SIZE
	printf("LOG: p = %d\n", p);

//elements assigned to the array
	for(i=0;i<SIZE;i++)
	{
		a[i] = nondet_unsigned_int();
		__CPROVER_assume(a[i]>0 && a[i]<=20);

//The condition below introduced bug which could not be verified by the harness
/*		for(j=i+1;j<SIZE;j++){
		__CPROVER_assume(a[i]!=a[j]);
		}
*/
		printf("LOG: a[%d] = %d\n", i, a[i]);
	}
	
//make the elements unique in the array
	for (i=0;i<SIZE;i++)
	{
		for(j=i+1;j<SIZE;j++){
		__CPROVER_assume(a[i]!=a[j]);
		}
	}

//element is there in the array
	m = a[n];
	printf("LOG: m = %d\n", m);
	k = mybinsearch(a, SIZE, m);
assert(k == 1);

//element is not in the array
	m = p;
	printf("LOG: m = %d\n", m);
	k = mybinsearch(a, SIZE, m);
assert(k == 0);


//assert(0);

}



