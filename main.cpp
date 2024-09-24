#include "Madi.cpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
  std::string path;

  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];

    if (arg == "-p" && i + 1 < argc) {
      path = argv[++i];
    }
  }

  if (path.empty() && argc > 1) {
    std::cerr << "No path specified." << std::endl;
    return 1;
  }

  Madi md = Madi();

  md.f_range();

  if (path.empty()) {
    md.print();
  } else {
    md.print(path);
  }

  return 0;
}
