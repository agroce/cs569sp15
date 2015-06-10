int arr[SIZE][SIZE];

int checkarr(int arr[SIZE][SIZE], int s) {
  int lsum = 0, i, j;
  for (i = 0; i < s; i++) {
    for (j = 0; j < s; j++) {
      lsum += arr[i][j];
    }
  }
  return lsum;
}

int main () {
  int i,j;
  int s = nondet_int();
  __CPROVER_assume(s>0);
  __CPROVER_assume(s<SIZE); 

  int sum1 = 0;
  int sum2 = 0;

  for (i = 0; i < s; i++) {
    for (j = 0; j < s; j++) {
      arr[i][j] = nondet_int();
      sum1 += arr[i][j];
    }
  }

  sum2 = checkarr(arr, s);

  assert(sum1 == sum2);
}
