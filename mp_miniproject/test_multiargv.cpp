#include <stdio.h>
#include <stdlib.h>

#include <iostream>
int main(int argc, char * argv[]) {
  int j;
  for (j = 0; j < argc; j++) {
    std::cout << "argv[" << j << "]: " << argv[j] << std::endl;
  }
  return EXIT_SUCCESS;
}
