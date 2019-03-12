#include "Matrix.h"
typedef Matrix<int> IntMatrix;

int main(void) {
  IntMatrix a(4, 5);
  std::cout << "a is:\n" << a << std::endl;
  for (int i = 0; i < a.getRows(); i++) {
    for (int j = 0; j < a.getColumns(); j++) {
      a[i][j] = i + j;
    }
  }
  std::vector<int> d = a[6];
  std::cout << "a[6] is:\n" << a << std::endl;
  return EXIT_SUCCESS;
}
