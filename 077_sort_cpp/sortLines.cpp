#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

void read_and_sort(std::istream & f) {
  std::string line;
  std::vector<std::string> data;

  while (getline(f, line)) {
    data.push_back(line);
  }
  if (!f.eof() && !f) {
    std::cerr << "Something wrong about reading the file.\n";
    exit(EXIT_FAILURE);
  }
  std::sort(data.begin(), data.end());

  std::vector<std::string>::iterator it = data.begin();
  while (it != data.end()) {
    std::cout << *it << "\n";
    ++it;
  }
}
int main(int argc, char ** argv) {
  if (argc == 1) {
    read_and_sort(std::cin);
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream ifs(argv[i]);
      if (ifs.is_open()) {
        read_and_sort(ifs);
      }
      else {
        std::cerr << "Could not open the file.\n";
        exit(EXIT_FAILURE);
      }
    }
  }
  return EXIT_SUCCESS;
}
