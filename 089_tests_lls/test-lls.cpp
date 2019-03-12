#include <assert.h>

#include <cstdlib>

#include "il.h"
void testList(void) {
  IntList test0;
  assert(test0.head == NULL);
  assert(test0.tail == NULL);
  assert(test0.size == 0);
  test0.addFront(3);
  assert(test0.head->next == NULL);
  assert(test0.tail->prev == NULL);
  test0.addFront(2);
  test0.addBack(4);
  assert(test0.size == 3);
  assert(test0[0] == 2 && test0[1] == 3 && test0[2] == 4);
  //test '='
  IntList test1;
  test1 = test0;
  assert(test1.head != NULL);
  test1.remove(2);
  test1.remove(4);
  assert(test1.head == test1.tail);

  //test remove
  IntList test2;
  test2 = test0;
  assert(test2.head != NULL);
  assert(test2.remove(5) == false);
  assert(test2.remove(2) == true);
  assert(test2.size == 2);
  assert(test2.head->prev == NULL);
  assert(test2.head->next->data == 4);
  assert(test2.head != NULL);
  assert(test2.head != test2.tail);
  assert(test2.tail != NULL);
  assert(test2.remove(4) == true);
  assert(test2.head == test2.tail);
  assert(test2.head->next == NULL);
  test2.remove(3);
  assert(test2.size == 0);
  assert(test2.head == NULL);
  assert(test2.tail == NULL);

  //test find
  IntList test3(test0);
  //assert(test3.head != NULL);
  assert(test3.find(2) == 0);
  //assert(test3.find(6));
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
