#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  uint64_t * counts;
  counts = new uint64_t[257]();
  FILE * f = fopen(fname, "r");
  int c;
  if (f == NULL) {
    perror("Can not open the file");
    exit(EXIT_FAILURE);
  }
  while ((c = getc(f)) != EOF) {
    counts[c]++;
  }
  counts[256] = 1;
  if (fclose(f) != 0) {
    perror("Can not close the file");
    exit(EXIT_FAILURE);
  }
  return counts;
}
