#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  kvarray_t * readKVs = malloc(sizeof(*readKVs));
  readKVs->pair = NULL;
  char * linep = NULL;
  size_t linecapp = 0;
  size_t n = 0;
  ssize_t len = 0;
  int i = 0;

  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file.");
    exit(EXIT_FAILURE);
  }

  while ((len = getline(&linep, &linecapp, f)) >= 0) {
    /*To find the index of the '=' in the line*/
    for (i = 0; i < len; i++) {
      if (linep[i] != '=') {
      }
      else {
        break;
      }
    }

    /*Check if the line contains '='*/
    if (i == len) {
      perror("This line doesn't contain '='");
      exit(EXIT_FAILURE);
    }

    /*Allocate memory for storing the current pair of key and value*/
    readKVs->pair = realloc(readKVs->pair, (n + 1) * sizeof(*readKVs->pair));
    readKVs->pair[n].key = malloc((i + 1) * sizeof(*(readKVs->pair[n].key)));
    readKVs->pair[n].value = malloc((len - 1 - i) * sizeof(*(readKVs->pair[n].value)));

    /*Change the first '=' to \0', marking the end of the key*/
    linep[i] = '\0';
    /*Change the '\n' to '\0', marking the end of the value*/
    linep[len - 1] = '\0';
    if ((i == 0) || (i == (len - 2))) {
      perror("Improper format. Proper format: key=value.");
      exit(EXIT_FAILURE);
    }

    /*Copy the part of key and value to the corresponding field of the struct*/
    strncpy(readKVs->pair[n].key, linep, i + 1);
    strncpy(readKVs->pair[n].value, linep + i + 1, len - 1 - i);

    /*Count the total of lines in the input file, meaning the size of the kvarray*/
    n++;
  }

  free(linep);
  if (fclose(f) != 0) {
    perror("Failed to close the input file.");
    exit(EXIT_FAILURE);
  }
  readKVs->length = n;
  return readKVs;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    free(pairs->pair[i].key);
    free(pairs->pair[i].value);
  }
  free(pairs->pair);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->pair[i].key, pairs->pair[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  int i = 0;

  for (i = 0; i < pairs->length; i++) {
    if (strcmp(pairs->pair[i].key, key) == 0) {
      break;
    }
  }
  if (i == pairs->length) {
    return NULL;
  }
  else {
    return pairs->pair[i].value;
  }
}
