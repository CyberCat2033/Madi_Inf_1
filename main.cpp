#include "Madi.cpp"

int main(int argc, char *argv[]) {
  Madi md = Madi(-100, 100, 201);
  md.f_range();
  md.print();
  md.print(false);

  return 0;
}
