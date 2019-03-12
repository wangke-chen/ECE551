#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned actual_ans;

  actual_ans = power(x, y);
  if (actual_ans == expected_ans) {
    return;
  }
  else {
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  unsigned x;
  unsigned y;
  unsigned expected_ans;

  x = -1;
  y = 3;
  expected_ans = -1;
  run_check(x, y, expected_ans);

  x = -1;
  y = 2;
  expected_ans = 1;
  run_check(x, y, expected_ans);

  x = 0;
  y = 1;
  expected_ans = 0;
  run_check(x, y, expected_ans);

  x = 0;
  y = 0;
  expected_ans = 1;
  run_check(x, y, expected_ans);

  return EXIT_SUCCESS;
}
