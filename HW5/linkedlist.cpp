#include "linkedlist.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <string>


using namespace std;

Node::Node(const nodedata mycargo, const unsigned int akey) : cargo(mycargo), key(akey), link(NULL) {}


CircledLinkedList::CircledLinkedList() : curposition(NULL), obcp(NULL), count(0), key(0) {}
CircledLinkedList::~CircledLinkedList()
{  
  if (curposition == NULL && key == 0)
    return;
  while (count != 0)
  {
    Node *node = curposition;
    curposition = node->link;
    count--;
    delete node;
  }
}
unsigned int CircledLinkedList::insert_atcurpoistion(nodedata cargo)
{
  unsigned int nodekey = key;
  Node *newNode = new Node(cargo, nodekey);
  if(curposition ==NULL &&  obcp==NULL){
    curposition = newNode;
    obcp = newNode;
  }
  newNode->link = curposition;
  obcp->link = newNode;
  obcp = newNode;
  key++;
  count++;
  return nodekey;
}

void CircledLinkedList::rotate_cur(unsigned int mth)
{
  if (curposition == NULL)
  {
    const char *errormsg = "Warning: accessing empty list";
    throw std::runtime_error(errormsg);
  }

  for(size_t k = 0; k< mth; k++){
    curposition = curposition->link;
    obcp = obcp->link;
  }
}

// We see the current position is 0th
nodedata CircledLinkedList::remove_cur()
{
  if (curposition == NULL)
  {
    const char *errormsg = "Warning: accessing empty list";
    throw std::runtime_error(errormsg);
  }

  Node *nodetodelete = curposition;
  curposition = nodetodelete->link;
  obcp->link = curposition;
  nodedata cargo = nodetodelete->cargo;
  delete nodetodelete;
  count--;
  return cargo;
}

void CircledLinkedList::printall()
{
  unsigned int temp_count = count;
  Node *node = curposition;
  while (temp_count != 0)
  {
    printf("node %d, the data is %d\n", node->key, node->cargo);
    node = node->link;
    temp_count--;
  }
}





