// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq1(int x) {
  int ans;

  ans = 4 * x - 3;
  return ans;
}

void printSeq1Range(int low, int high) {
  if (low >= high) {
    printf("\n");
    return;
  }

  for (int i = low; i < (high - 1); i++) {
    printf("%d, ", seq1(i));
  }
  printf("%d", seq1(high - 1));
  printf("\n");
  return;
}

int main(void) {
  int x;

  /*test1*/
  x = 6;
  printf("seq1(%d) = %d\n", x, seq1(x));

  /*test2*/
  x = 0;
  printf("seq1(%d) = %d\n", x, seq1(x));

  /*test3*/
  x = -1;
  printf("seq1(%d) = %d\n", x, seq1(x));

  /*test4*/
  printSeq1Range(-1, 6);

  /*test5*/
  printSeq1Range(6, 6);

  /*test6*/
  printSeq1Range(-5, -1);

  /*test7*/
  printSeq1Range(7, 3);

  /*test8*/
  printSeq1Range(-1, -3);

  /*test9*/
  printSeq1Range(7, 12);

  return EXIT_SUCCESS;
}
