#include "Madi.cpp"

int main(int argc, char *argv[]) {
  Madi md = Madi(-3, 6, 4);
  md.f_range();
  md.print();
  md.print(false);

  return 0;
}
