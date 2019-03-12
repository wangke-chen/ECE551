// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq2(int x) {
  int ans;

  if ((x == -1) || (x == -2)) {
    return -1;
  }
  else {
    if (x < 0) {
      ans = seq2(x + 1) - 2 * (x + 2);
      return ans;
    }
    else {
      ans = seq2(x - 1) + 2 * (x + 1);
      return ans;
    }
  }
}

int sumSeq2(int low, int high) {
  int sum = 0;

  if (low >= high) {
    return 0;
  }

  for (int i = low; i < high; i++) {
    sum = sum + seq2(i);
  }
  return sum;
}

int main(void) {
  int x;
  int low;
  int high;

  x = -1;
  printf("seq2(%d) = %d\n", x, seq2(x));

  x = 0;
  printf("seq2(%d) = %d\n", x, seq2(x));

  x = -4;
  printf("seq2(%d) = %d\n", x, seq2(x));

  x = -7;
  printf("seq2(%d) = %d\n", x, seq2(x));

  low = 0;
  high = 7;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = -9;
  high = -2;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = -5;
  high = 3;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = 3;
  high = 6;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = 4;
  high = 1;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = -1;
  high = -3;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  low = 4;
  high = 4;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  return EXIT_SUCCESS;
}
