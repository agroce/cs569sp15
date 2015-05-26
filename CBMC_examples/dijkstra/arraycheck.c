int main () {

  int a[SIZE];
  //initialize array a

  r = find(a, item);

  if (r >= 0) {
    assert (a[r] == item);
  } else {
    int v = nondet_int();
    __CPROVER_assume((v >= 0) && (v < SIZE));
    assert (a[v] != item);
  }

}
