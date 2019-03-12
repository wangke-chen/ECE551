#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
void testList(void);
template<typename T>
class LinkedList
{
 private:
  class Node
  {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(T data, Node * next, Node * prev) : data(data), next(next), prev(prev) {}
  };
  Node * head;
  Node * tail;
  class IndexError : public std::exception
  {
    const char * what() { return "Index out of bound."; }
  };

 public:
  void addFront(const T & item);
  void addBack(const T & item);
  bool remove(const T & item);
  T & operator[](int index);
  const T & operator[](int index) const;
  int find(const T & item) const;
  LinkedList() : head(NULL), tail(NULL) {}
  LinkedList(const LinkedList & rhs);
  LinkedList & operator=(const LinkedList & rhs);
  ~LinkedList();
  int getSize() const;
  friend void testList(void);
};

template<typename T>
void LinkedList<T>::addFront(const T & item) {
  head = new Node(item, head, NULL);
  if (tail == NULL) {
    tail = head;
  }
  else {
    head->next->prev = head;
  }
}

template<typename T>
void LinkedList<T>::addBack(const T & item) {
  tail = new Node(item, NULL, tail);
  if (head == NULL) {
    head = tail;
  }
  else {
    tail->prev->next = tail;
  }
}

template<typename T>
bool LinkedList<T>::remove(const T & item) {
  Node * temp;
  for (temp = head; temp != NULL && !(temp->data == item); temp = temp->next) {
  }
  if (temp == NULL) {
    return false;
  }
  if (tail == head) {
    head = NULL;
    tail = NULL;
  }
  else if (temp == head) {
    head = temp->next;
    head->prev = NULL;
  }
  else if (temp == tail) {
    tail = temp->prev;
    tail->next = NULL;
  }
  else {
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
  }
  delete temp;
  return true;
}

template<typename T>
T & LinkedList<T>::operator[](int index) {
  Node * temp;
  for (temp = head; temp != NULL && index > 0; temp = temp->next) {
    --index;
  }
  if (temp == NULL || index < 0) {
    throw IndexError();
  }
  return temp->data;
}

template<typename T>
const T & LinkedList<T>::operator[](int index) const {
  Node * temp;
  for (temp = head; temp != NULL && index > 0; temp = temp->next) {
    --index;
  }
  if (temp == NULL) {
    throw IndexError();
  }
  return temp->data;
}

template<typename T>
int LinkedList<T>::find(const T & item) const {
  Node * temp;
  int index = 0;
  for (temp = head; temp != NULL && !(temp->data == item); temp = temp->next) {
    ++index;
  }
  if (temp == NULL) {
    return -1;
  }
  return index;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL) {
  for (Node * temp = rhs.head; temp != NULL; temp = temp->next) {
    addBack(temp->data);
  }
}

template<typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList & rhs) {
  Node * next = NULL;
  for (Node * temp = head; temp != NULL; temp = next) {
    next = temp->next;
    delete temp;
  }
  head = NULL;
  tail = NULL;
  for (Node * temp = rhs.head; temp != NULL; temp = temp->next) {
    addBack(temp->data);
  }
  return *this;
}

template<typename T>
LinkedList<T>::~LinkedList() {
  Node * next = NULL;
  for (Node * temp = head; temp != NULL; temp = next) {
    next = temp->next;
    delete temp;
  }
}

template<typename T>
int LinkedList<T>::getSize() const {
  int size = 0;
  for (Node * temp = head; temp != NULL; temp = temp->next) {
    ++size;
  }
  return size;
}

#endif
