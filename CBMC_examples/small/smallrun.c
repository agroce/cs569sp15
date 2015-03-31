#include <stdio.h>
#include <assert.h>
//unsigned int nondet_int();

int main () {

  unsigned int a = 0;
  unsigned int b = 4294967294U;
  
  long diff = a - b;
  long diff2 = diff;

  printf ("diff = %ld\n", diff);

  if (diff < 0) {
    diff2 = -diff;
    //__CPROVER_assume(diff2 != diff);
  }

  printf ("LOG: a = %u, b = %u, diff = %ld\n", a,b, diff);

  //__CPROVER_assume(diff2 < BOUND);

  /*

  while (a < b) {
    b--;
  }
  while (b < a) {
    a--;
  }

  */

  printf ("LOG: after loop a = %u, b = %u\n", a,b);
  
  assert (a == b);
}
