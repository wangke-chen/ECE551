// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y) {
  int ans;

  ans = -3 * x + y * (x + 2);
  return ans;
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int sum = 0;

  if ((xLow >= xHi) || (yLow >= yHi)) {
    return 0;
  }
  for (int i = xLow; i < xHi; i++) {
    for (int j = yLow; j < yHi; j++) {
      if ((seq3(i, j) % 2) == 0) {
        sum++;
      }
    }
  }
  return sum;
}

int main(void) {
  int x;
  int y;
  int xLow, xHi, yLow, yHi;

  x = 0;
  y = 0;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  x = 0;
  y = 4;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  x = -2;
  y = 0;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  x = -5;
  y = -5;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  x = -3;
  y = 2;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  x = 7;
  y = -2;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  x = 6;
  y = 7;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  xLow = -2;
  xHi = 3;
  yLow = -4;
  yHi = 1;
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  xLow = 0;
  xHi = 2;
  yLow = 0;
  yHi = 3;
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  xLow = -2;
  xHi = -2;
  yLow = 2;
  yHi = 3;
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  xLow = 2;
  xHi = 3;
  yLow = 3;
  yHi = -2;
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  xLow = -3;
  xHi = -1;
  yLow = -1;
  yHi = 2;
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  return EXIT_SUCCESS;
}
