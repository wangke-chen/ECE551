#include <assert.h>

#include <iostream>

#include "bstmap.h"
#include "map.h"
void test() {
  BstMap<int, int> empty1;
  BstMap<int, int> empty2(empty1);
  empty2.add(4, 4);
  BstMap<int, int> m;
  assert(m.root == NULL);
  m.add(60, 60);
  m.add(60, 55);
  assert(m.root->value == 55);
  m.add(19, 19);
  m.add(93, 93);
  m.add(4, 4);
  m.add(1, 1);
  m.add(11, 11);
  m.add(25, 25);
  m.add(21, 21);
  m.add(35, 35);
  m.add(84, 84);
  BstMap<int, int> * n = &m;
  assert(n->root->right->key == 93);
  assert(m.root->right->key == 93);
  assert(m.root->right->left->key == 84);
  assert(m.root->left->right->key == 25);
  assert(m.root->left->right->left->key == 21);
  assert(m.root->left->left->left->key == 1);
  try {
    int v;
    v = m.lookup(60);
    std::cout << v << " ";
    assert(v == 55);
  }
  catch (const std::invalid_argument & e) {
    std::cout << e.what() << "\n";
  }
  m.remove(19);
  assert(m.root->left->key == 11);
  assert(m.root->left->left->right == NULL);
}

int main() {
  test();
}
