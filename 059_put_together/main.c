#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * c = createCounts();
  char * linep = NULL;
  size_t linecapp = 0;
  ssize_t len = 0;

  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("Could not open the file.");
    exit(EXIT_FAILURE);
  }

  while ((len = getline(&linep, &linecapp, f)) >= 0) {
    linep[len - 1] = '\0';
    addCount(c, lookupValue(kvPairs, linep));
  }

  free(linep);
  if (fclose(f) != 0) {
    perror("Failed to close the input file.");
    exit(EXIT_FAILURE);
  }

  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc <= 1) {
    perror("At least one list.txt");
    exit(EXIT_FAILURE);
  }
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      perror("Could not open the file.");
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      perror("Could not close the input file.");
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
