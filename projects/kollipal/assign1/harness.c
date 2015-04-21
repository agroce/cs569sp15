#include <stdio.h>
#include "cbmc.h"
#include <assert.h>
int nondet_int();
int main()
{
	int i,count = 0;
	int a[SIZE];
	printf("LOG: SIZE = %d\n", SIZE);
	for(i=0; i< SIZE; i++)
	{
		a[i] = nondet_int();
		//__CPROVER_assume(a[i] > 1 && a[i] < 5);
		printf("LOG: a[%d] = %d\n", i, a[i]);
	}
	int b[SIZE];
	for(i=0; i< SIZE; i++)
	{
		b[i] = nondet_int();
		//__CPROVER_assume(b[i] > 5 && b[i] < 10);
		printf("LOG: b[%d] = %d\n", i, b[i]);
	}
	int merged[SIZE*2];
	merge(a, b, SIZE, merged);
	mysort(merged, SIZE*2);
	for(i=1; i< SIZE*2; i++)
    {
        if(merged[i] >= merged[i-1])
        {
            count++;
        }
    }
    assert(count == (SIZE*2)-1);
    assert(sizeof(merged) == sizeof(a)+ sizeof(b));
	assert(isSubset(merged, SIZE*2, a, SIZE) == 1);
	assert(isSubset(merged, SIZE*2, b, SIZE) == 1);
	   // merged[SIZE*2]= 24;
}