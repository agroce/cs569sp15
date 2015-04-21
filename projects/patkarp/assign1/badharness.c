
#include <stdio.h>
#include "mysort.h"
#include <assert.h>
//#include "mysort.c"
int heap[SIZE];

int nondet_int();
unsigned int nondet_unsigned_int();

int main () 
{
  int i, v, last;
  int refc = 0;
  int acount = 0;
  unsigned int s = nondet_unsigned_int();
  __CPROVER_assume (s <= SIZE);
  int val = nondet_int();
  printf ("LOG: s = %u, val = %d\n", s, val);
  for (i = 0; i < s; i++) 
  {
    v = nondet_int();
    printf ("LOG: a[%d] = %d\n", i, v);
    heap[i] = v;
    if (v == val) 
    {
      refc++;
    }
  }

  sort(heap,s); 
  printf ("LOG: sorted HEAP\n");


  if (s > 0) 
  {
    last = heap[0];
    if (heap[0] == val) 
    {
      acount++;
    }
  }
  for (i = 1; i < s; i++) 
  {
    printf ("LOG: last = %d, a[%d] = %d\n", last, i, heap[i]);
    assert (heap[i] >= last);
    if (heap[i] == val) 
    {
      acount++;
    }
    last = heap[i];
  }

  printf ("LOG: refc = %d, acount = %d\n", refc, acount);
  assert (refc == acount);
  
 //Verify values in the Heap and compare with each other
  for(i=0;i<SIZE;i++) 
  {
    heap[i] = nondet_unsigned_int();
    __CPROVER_assume(heap[i]>0 && heap[i]<=SIZE);

//
  for(j=i+1;j<SIZE;j++)
    {
    __CPROVER_assume(heap[i]!=heap[j]);
    }

    printf("LOG: a[%d] = %d\n", i, heap[i]);
  }
 // assert(0);
}
