#if !defined LINKEDLIST_H
#define LINKEDLIST_H

typedef unsigned int nodedata;

struct Node
{
  const nodedata cargo;
  const unsigned int key;
  Node *link;
  Node(const nodedata mycargo, const unsigned int akey);
  ~Node() {}
};

class CircledLinkedList
{
public:
  CircledLinkedList();
  ~CircledLinkedList();
  unsigned int insert_atcurpoistion(nodedata);
  nodedata remove_cur();
  void rotate_cur(unsigned int mth);
  void printall();

private:
  Node *curposition;
  Node *obcp; // one node before current position
  // Node *head;
  unsigned int count;
  unsigned int key;
};

#endif