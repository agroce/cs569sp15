int nondet_int();

int main () {
  int x = nondet_int();
  while (1) {
    x++;
  }
  assert(0);
}
