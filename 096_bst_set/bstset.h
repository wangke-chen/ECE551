#include <cstdlib>
#include <exception>

#include "set.h"

template<typename K>
class BstSet : public Set<K>
{
 protected:
  class Node
  {
   public:
    K key;
    Node * left;
    Node * right;
    Node(const K & key) : key(key), left(NULL), right(NULL) {}
  };
  Node * root;
  void copy(Node ** current, const Node * copyFrom);
  void destroy(Node * current);
  Node * remove(Node * current, const K & key) {
    if (current == NULL) {
      return NULL;
    }
    else {
      if (current->key > key) {
        Node * newLeft = remove(current->left, key);
        current->left = newLeft;
        return current;
      }
      else if (current->key < key) {
        Node * newRight = remove(current->right, key);
        current->right = newRight;
        return current;
      }
      else {
        if (current->left == NULL) {
          Node * temp = current->right;
          delete current;
          return temp;
        }
        else if (current->right == NULL) {
          Node * temp = current->left;
          delete current;
          return temp;
        }
        else {
          Node ** temp = &current->left;
          while ((*temp)->right != NULL) {
            temp = &(*temp)->right;
          }
          current->key = (*temp)->key;

          Node * n = *temp;
          *temp = (*temp)->left;
          delete n;
          return current;
        }
      }
    }
  }

 public:
  BstSet() : root(NULL) {}
  BstSet(const BstSet & m) : root(NULL) { copy(&root, m.root); }
  virtual void add(const K & key);
  virtual bool contains(const K & key) const;
  virtual void remove(const K & key);
  virtual ~BstSet<K>() { destroy(root); }
  const BstSet & operator=(const BstSet & m) {
    if (&m != this) {
      BstSet temp(m);
      Node * t = root;
      root = temp.root;
      temp.root = t;
    }
    return *this;
  }
  friend void test();
};

template<typename K>
void BstSet<K>::copy(Node ** current, const Node * copyFrom) {
  if (copyFrom != NULL) {
    *current = new Node(copyFrom->key);
    copy(&(*current)->left, copyFrom->left);
    copy(&(*current)->right, copyFrom->right);
  }
}

template<typename K>
void BstSet<K>::destroy(Node * current) {
  if (current != NULL) {
    destroy(current->left);
    destroy(current->right);
    delete current;
  }
}

template<typename K>
void BstSet<K>::add(const K & key) {
  Node ** current = &root;
  while (*current != NULL) {
    if (key < (*current)->key) {
      current = &(*current)->left;
    }
    else {
      current = &(*current)->right;
    }
  }
  *current = new Node(key);
}

template<typename K>
bool BstSet<K>::contains(const K & key) const {
  Node * current = root;
  while (current != NULL) {
    if (key == current->key) {
      break;
    }
    else if (key < current->key) {
      current = current->left;
    }
    else {
      current = current->right;
    }
  }
  if (current == NULL) {
    return false;
  }
  return true;
}

template<typename K>
void BstSet<K>::remove(const K & key) {
  root = remove(root, key);
}
