#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix inputFileName");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  char matrix[10][10];
  int c;

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 11; j++) {
      c = fgetc(f);
      if (j == 10) {
        if (c == '\n') {
          continue;
        }
        else {
          perror("Something Wrong!");
          return EXIT_FAILURE;
        }
      }
      else {
        matrix[i][j] = c;
      }
    }
  }

  if ((c = fgetc(f)) != EOF) {
    perror("The file has too many columns");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 9; j >= 0; j--) {
      printf("%c", matrix[j][i]);
    }
    printf("\n");
  }

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
