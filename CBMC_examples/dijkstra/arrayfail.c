#define SIZE 3

int arr[SIZE][SIZE];

int checkarr(int arr[SIZE][SIZE]) {
  int lsum = 0, i, j;
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      lsum += arr[i][j];
    }
  }
  return lsum;
}

int main () {
  int i,j;

  int sum1 = 0;
  int sum2 = 0;

  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      arr[i][j] = nondet_int();
      sum1 += arr[i][j];
    }
  }

  sum2 = checkarr(arr);

  assert(sum1 == sum2);
}
