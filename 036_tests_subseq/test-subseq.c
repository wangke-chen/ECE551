#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run_check(int * array, size_t n, size_t expected_ans) {
  size_t actual_ans = maxSeq(array, n);

  if (actual_ans == expected_ans) {
    return;
  }
  else {
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int array0[2] = {0, 1};
  size_t n0 = 2;
  size_t expected_ans0 = 2;
  run_check(array0, n0, expected_ans0);

  int array1[3] = {0, 0, 0};
  size_t n1 = 3;
  size_t expected_ans1 = 1;
  run_check(array1, n1, expected_ans1);

  int array2[5] = {1, 1, 3, 2, 5};
  size_t n2 = 5;
  size_t expected_ans2 = 2;
  run_check(array2, n2, expected_ans2);

  int array3[0];
  size_t n3 = 0;
  size_t expected_ans3 = 0;
  run_check(array3, n3, expected_ans3);

  printf("Success");
  return EXIT_SUCCESS;
}
