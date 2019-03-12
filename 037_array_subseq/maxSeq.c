#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t max_seq[n];
  size_t i = 0;
  size_t j = 0;

  if (n == 0) {
    return 0;
  }

  for (i = 0; i < n; i++) {
    max_seq[i] = 0;
  }

  max_seq[0] = 1;

  for (i = 1; i < n; i++) {
    if (array[i - 1] < array[i]) {
      max_seq[j]++;
    }
    else {
      j++;
      max_seq[j] = 1;
    }
  }

  for (j = 1; j < n; j++) {
    if (max_seq[0] < max_seq[j]) {
      max_seq[0] = max_seq[j];
    }
    else {
      continue;
    }
  }
  return max_seq[0];
}
