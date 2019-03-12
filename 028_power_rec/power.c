unsigned power(unsigned x, unsigned y) {
  if (x == 0) {
    if (y == 0) {
      return 1;
    }
    else {
      return 0;
    }
  }

  if (y == 0) {
    return 1;
  }
  else {
    return x * power(x, y - 1);
  }
}
