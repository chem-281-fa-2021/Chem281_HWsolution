
#include "queue.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <cmath>

using namespace std;

QueueNode::QueueNode(const nodedata mycargo) : cargo(mycargo), next(NULL) {}
QueueNode::QueueNode() :  next(NULL) {}

Queue::Queue()
{
  QueueNode *dummy = new QueueNode;
  head = tail = dummy;
};
Queue::~Queue()
{
  while (!checkempty())
  {
    remove();
  }
  // delete tail;
};

void Queue::insert(nodedata &cargo)
{
  QueueNode *nn = new QueueNode(cargo);
  head->next = nn;
  head = nn;
}
nodedata Queue::remove()
{
  if(head == tail)
    throw invalid_argument("the queue is empty.");
  QueueNode *tn = tail->next;
  nodedata nn = tn->cargo;
  delete tail;
  tail = tn;
  return nn;
}
bool Queue::checkempty()
{
  return head == tail;
}
void Queue::printall()
{
  QueueNode *temp = tail;
  while (temp != head)
  {
    temp = temp->next;
    printf("the data is %d\n", temp->cargo);
  }
}

