#if !defined QUEUE_H
#define QUEUE_H

typedef unsigned int nodedata;

struct QueueNode
{
  nodedata cargo;
  QueueNode *next;
  QueueNode();
  QueueNode(const nodedata mycargo);
};

class Queue
{
public:
  Queue();
  ~Queue();
  void insert(nodedata &cargo);
  nodedata remove();
  bool checkempty();
  void printall();

private:
  QueueNode *head;
  QueueNode *tail;
};

#endif