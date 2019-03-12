#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * c = malloc(sizeof(*c));
  c->keyCount = NULL;
  c->unknownCount = 0;
  c->size = 0;
  return c;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknownCount++;
    return;
  }
  else {
    for (int i = 0; i < c->size; i++) {
      if (strcmp(c->keyCount[i].name, name) == 0) {
        c->keyCount[i].times++;
        return;
      }
    }
    c->size++;
    c->keyCount = realloc(c->keyCount, (c->size) * sizeof(*c->keyCount));
    int len = strlen(name) + 1;
    c->keyCount[c->size - 1].name = malloc(len * sizeof(*(c->keyCount[c->size - 1].name)));
    strncpy(c->keyCount[c->size - 1].name, name, len);
    c->keyCount[c->size - 1].times = 1;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %d\n", c->keyCount[i].name, c->keyCount[i].times);
  }
  if (c->unknownCount != 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unknownCount);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    free(c->keyCount[i].name);
  }
  free(c->keyCount);
  free(c);
}
