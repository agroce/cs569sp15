#include <stdio.h>
#include <assert.h>
#include "sort.h"

int a[SIZE];

int nondet_int(); //returns a nondeterministic value
unsigned int nondet_unsigned_int(); //returns an unsigned nondeterministic value

int main ()
{
  //checks whether the sorted array and unsorted array are the permutation of each other.
  //If the arrays are not permutations of each other, so one of them could not be the sorted version of the other.
  int i, v, last, val;
  int refc = 0;
  int acount = 0;
  unsigned int s = nondet_unsigned_int();
  __CPROVER_assume (s <= SIZE);
  int val = nondet_int();
  printf ("LOG: s = %u, val = %d\n", s, val);
  
for (i = 0; i < s; i++) {
    v = nondet_int();
    printf ("LOG: a[%d] = %d\n", i, v);
    a[i] = v;
    if (v == val) {
      refc++; //counts the number of times which a[i] has the same value as val.
    }
  }

  mysort(a,s); 
  printf ("LOG: sorted a\n");

   //checks whether the array is sorted or not

  if (s > 0) {
    last = a[0];
    if (a[0] == val) {
      acount++;
    }
  }
  for (i = 1; i < s; i++) {
    printf ("LOG: last = %d, a[%d] = %d\n", last, i, a[i]);
    assert (a[i] >= last);
    if (a[i] == val) {
      acount++;
    }
    last = a[i];
  }

  printf ("LOG: refc = %d, acount = %d\n", refc, acount);
  assert (refc == acount); //asserts whether the number of occurrence of values are the same in the array before and after sorting.
  //  assert(0);
}
