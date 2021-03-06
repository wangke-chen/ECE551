#include <assert.h>

#include <iostream>

#include "bstset.h"
#include "set.h"
void test() {
  BstSet<int> empty1;
  BstSet<int> empty2(empty1);
  empty2.add(4);
  BstSet<int> m;
  assert(m.root == NULL);
  m.add(60);
  m.add(60);
  m.add(19);
  m.add(93);
  m.add(4);
  m.add(1);
  m.add(11);
  m.add(25);
  m.add(21);
  m.add(35);
  m.add(84);
  BstSet<int> * n = &m;
  assert(n->root->right->right->key == 93);
  assert(m.root->right->right->key == 93);
  assert(m.root->right->right->left->key == 84);
  assert(m.root->left->right->key == 25);
  assert(m.root->left->right->left->key == 21);
  assert(m.root->left->left->left->key == 1);

  assert(m.contains(60));

  m.remove(19);
  assert(m.root->left->key == 11);
  assert(m.root->left->left->right == NULL);
}

int main() {
  test();
}
