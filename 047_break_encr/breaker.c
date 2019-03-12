#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void frequency_count(FILE * f, int * fre_count) {
  int c, index;

  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      index = c - 'a';
      fre_count[index]++;
    }
  }
}

int max(int * fre_count) {
  int index = 0;
  int M = fre_count[0];

  for (int i = 1; i < 26; i++) {
    if (fre_count[i] > M) {
      index = i;
      M = fre_count[i];
    }
  }
  return index;
}

int breaker(FILE * f) {
  int fre_count[26] = {0};
  int key;

  frequency_count(f, fre_count);

  int i = max(fre_count);

  key = i - 4;
  if (key < 0) {
    key += 26;
  }

  return key;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  int key = breaker(f);
  fprintf(stdout, "%d\n", key);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
