#include <stdio.h>

int nondet_int();

int main () {
  int a = nondet_int();
  int b = nondet_int();
  __CPROVER_assume((a > -10) && (a < 10) && (b > -10) && (b < 10));
  printf("a + b = %d\n", a + b);
  a = a + 2;
  b = b + 3;
  assert ((a + b) != 0);
}
