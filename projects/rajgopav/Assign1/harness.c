#include <stdio.h>
#include "mergesort.h"
#include "assert.h"

int a[SIZE];

int nondet_int(); // Returns an arbitary integer value
unsigned int nondet_unsigned_int(); // Returns an unsigned arbitary integer value
//The following harness checks the following:
//1. Checks whether the array is sorted  
//2. Checks whether times of values = val keep the same
int main ()
 {
        int i, v, last, val;
        int refc = 0;
        int acount = 0;
        unsigned int s = nondet_unsigned_int();
        __CPROVER_assume (s <= SIZE);
        int val = nondet_int();
        printf ("LOG: size = %u, val = %d\n", SIZE, val);

        for (i = 0; i < SIZE; i++)
        {
                v = nondet_int();
                printf ("LOG: a[%d] = %d\n", i, v);
                a[i] = v;

                if (v == val)
                {
                        refc++;      // Record the number of times a[i] has the same value is equal val.
                }
        }

        mergeSort(a,0,SIZE-1);
        printf ("LOG: sorted a\n");

        //1. Checks whether the array is sorted
        if (SIZE > 0)
        {
                last = a[0];

                if (a[0] == val)
                {
                        acount++;
                }
        }

        for (i = 1; i < SIZE; i++)
        {
                printf ("LOG: last = %d, a[%d] = %d\n", last, i, a[i]);
                printf("Size of the array: %d" , SIZE);
                printf("LOG: a[%d] : %d ",i,a[i]);
                assert (a[i] >= last);  // Assert if the first element is bigger than the last element

                if (a[i] == val)
                {
                        acount++;
                }

                last = a[i];  // Update the last element
        }

        printf ("LOG: refc = %d, acount = %d\n", refc, acount);
        assert (refc == acount);  // Assert whether times of values = val keep the same
        
// Verify the values that are present in the sorted array
  for(i=0;i<SIZE;i++) 
  {
    a[i] = nondet_unsigned_int();
    __CPROVER_assume(a[i]>0 && a[i]<=SIZE);

  for(j=i+1;j<SIZE;j++)
    {
    __CPROVER_assume(a[i]!=a[j]);
    }

    printf("LOG: a[%d] = %d\n", i, a[i]);
  }
  assert(0);
}
