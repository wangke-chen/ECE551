#include <cmath>
#include <cstdlib>
#include <exception>
#include <iostream>

#include "function.h"

extern int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int>
{
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  unsigned n;
  if (high > low) {
    n = log2(high - low) + 1;
  }
  else {
    n = 1;
  }
  CountedIntFn F(n, f, mesg);
  int actual_ans = binarySearchForZero(&F, low, high);
  if (actual_ans != expected_ans) {
    fprintf(stderr, "The ans does not match for %s\n", mesg);
    exit(EXIT_FAILURE);
  }
}

class SinCheck : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class LinearCheck : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return arg; }
};

int main() {
  SinCheck sinCheck;
  check(&sinCheck, 0, 150000, 52359, "SinCheck");

  LinearCheck linear;
  check(&linear, 1, 1, 1, "LinearCheck");
  check(&linear, 0, 2, 0, "LinearCheck");
  check(&linear, -2, 0, -1, "LinearCheck");
  check(&linear, 1, 2, 1, "LinearCheck");
  check(&linear, -1, 3, 0, "LinearCheck");
  exit(EXIT_SUCCESS);
}
