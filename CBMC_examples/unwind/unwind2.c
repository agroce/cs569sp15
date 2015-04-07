int nondet_int();

int main () {
  int x = nondet_int();
  while (x < 1000) {
    x++;
  }
  assert(0);
}
