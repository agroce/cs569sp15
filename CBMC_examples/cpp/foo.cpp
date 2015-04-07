// classes example
//using namespace std;
#include "assert.h"


class Rectangle {
  int width, height;
public:
  void set_values (int,int);
  int area() {return width*height;}
};

void Rectangle::set_values (int x, int y) {
  width = x;
  height = y;
}

int main () {

  Rectangle rect;
  Rectangle * r2 = new Rectangle();
  rect.set_values (3,4);
  r2->set_values(5,6);
  //  cout << "area: " << rect.area();
  assert (rect.area() == 12);
  assert (r2->area() == 31);
  return 0;
}
