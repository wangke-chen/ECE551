#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);

  for (size_t i = 0; i < count; i++) {
    printf("%s", data[i]);
  }
  return;
}

int main(int argc, char ** argv) {
  ssize_t len;
  size_t count = 0;
  size_t sz = 0;
  char * data[50] = {NULL};

  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    while ((len = getline(&data[count], &sz, stdin)) >= 0) {
      count++;
    }
    sortData(data, count);
    for (size_t i = 0; i <= count; i++) {
      free(data[i]);
    }
  }
  if (argc > 1) {
    for (int j = 1; j < argc; j++) {
      FILE * f = fopen(argv[j], "r");
      if (f == NULL) {
        perror("Could not open the file");
        return EXIT_FAILURE;
      }
      sz = 0;
      char * data[50] = {NULL};
      count = 0;
      while ((len = getline(&data[count], &sz, f)) >= 0) {
        count++;
      }
      sortData(data, count);
      for (size_t i = 0; i <= count; i++) {
        free(data[i]);
      }

      if (fclose(f) != 0) {
        perror("Failed to close the input file");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
