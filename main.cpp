#include "Madi.cpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
  std::string path;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    // Проверяем аргумент '-p'
    if (arg == "-p" && i + 1 < argc) {
      std::string path = argv[++i]; // Следующий аргумент после '-p' будет путём
    }
  }

  if (path.empty() && argc > 0) {
    std::cerr << "No path specified." << std::endl;
    return 1;
  }

  Madi md = Madi();
  md.f_range();
  md.print();
  md.print(false);

  return 0;
}
