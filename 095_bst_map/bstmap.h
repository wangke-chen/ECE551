#include <cstdlib>
#include <exception>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V>
{
 protected:
  class Node
  {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(const K & key, const V & value) : key(key), value(value), left(NULL), right(NULL) {}
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
          current->value = (*temp)->value;
          Node * n = *temp;
          *temp = (*temp)->left;
          delete n;
          return current;
        }
      }
    }
  }

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & m) : root(NULL) { copy(&root, m.root); }
  virtual void add(const K & key, const V & value);
  virtual const V & lookup(const K & key) const throw(std::invalid_argument);
  virtual void remove(const K & key);
  virtual ~BstMap<K, V>() { destroy(root); }
  const BstMap & operator=(const BstMap & m) {
    if (&m != this) {
      BstMap temp(m);
      Node * t = root;
      root = temp.root;
      temp.root = t;
    }
    return *this;
  }
  friend void test();
};

template<typename K, typename V>
void BstMap<K, V>::copy(Node ** current, const Node * copyFrom) {
  if (copyFrom != NULL) {
    *current = new Node(copyFrom->key, copyFrom->value);
    copy(&(*current)->left, copyFrom->left);
    copy(&(*current)->right, copyFrom->right);
  }
}

template<typename K, typename V>
void BstMap<K, V>::destroy(Node * current) {
  if (current != NULL) {
    destroy(current->left);
    destroy(current->right);

    delete current;
  }
}

template<typename K, typename V>
void BstMap<K, V>::add(const K & key, const V & value) {
  Node ** current = &root;
  while (*current != NULL) {
    if (key == (*current)->key) {
      (*current)->value = value;
      return;
    }
    else if (key < (*current)->key) {
      current = &(*current)->left;
    }
    else {
      current = &(*current)->right;
    }
  }
  *current = new Node(key, value);
}

template<typename K, typename V>
const V & BstMap<K, V>::lookup(const K & key) const throw(std::invalid_argument) {
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
    throw std::invalid_argument("Can not find the key\n");
  }
  return current->value;
}

template<typename K, typename V>
void BstMap<K, V>::remove(const K & key) {
  root = remove(root, key);
}
