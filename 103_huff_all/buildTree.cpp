#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;

  for (int i = 0; i < 257; i++) {
    if (counts[i] > 0) {
      Node * node = new Node(i, counts[i]);
      pq.push(node);
    }
  }
  while (pq.size() > 1) {
    Node * node1 = pq.top();
    pq.pop();
    Node * node2 = pq.top();
    pq.pop();
    Node * node = new Node(node1, node2);
    pq.push(node);
  }
  return pq.top();
}
