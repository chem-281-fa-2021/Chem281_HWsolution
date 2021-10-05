#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

typedef unsigned int nodedata;

struct Node
{
  const nodedata cargo;
  const unsigned int key;
  Node *link;
  Node(const nodedata mycargo, const unsigned int akey) : cargo(mycargo), key(akey), link(NULL) {}
  ~Node() {}
};

class LinkedList
{
public:
  LinkedList();
  ~LinkedList();
  unsigned int insert(nodedata);
  unsigned int insertafterkey(nodedata, unsigned int key);
  void remove(unsigned int);
  nodedata getnode();
  nodedata getnodebykey(unsigned int key);
  void printall();

private:
  Node *head;
  unsigned int count;
  unsigned int key;
};

LinkedList::LinkedList() : head(NULL), count(0), key(0) {}

LinkedList::~LinkedList()
{
  if (head == NULL && key == 0)
    return;
  while (head)
  {
    Node *node = head;
    head = node->link;
    count--;
    delete node;
    if (count == 0)
      break; // possibly corrupted list
  }
  if ((count == 0 && head != NULL) || (head == NULL && count != 0))
  {
    const char *errormsg = "Warning: inconsistent list";
    cout << errormsg << endl;
  }
}

void LinkedList::printall()
{
  if (head == NULL)
    return;
  unsigned int temp_count = count;
  Node *node = head;
  while (node)
  {
    printf("node %d, the data is %d\n", node->key, node->cargo);
    node = node->link;
    temp_count--;
    if (temp_count == 0)
      break; // possibly corrupted list
  }
  if ((temp_count == 0 && node != NULL) || (node == NULL && temp_count != 0))
  {
    const char *errormsg = "Warning: inconsistent list when print list";
    cout << errormsg << endl;
  }
}

unsigned int LinkedList::insert(nodedata cargo)
{
  unsigned int nodekey = key;
  Node *newNode = new Node(cargo, nodekey);
  newNode->link = head;
  head = newNode;
  key++;
  count++;
  return nodekey;
}

unsigned int LinkedList::insertafterkey(nodedata cargo, unsigned int akey)
{
  if (head == NULL)
  {
    const char *errormsg = "Warning: accessing empty list";
    throw std::runtime_error(errormsg);
  }
  Node *node = head;
  while (node->key != akey)
  {
    node = node->link;
    if (node == NULL)
    {
      char error[100];
      sprintf(error, "Warning: When inserting after key, there is no keys satisfied k = %d ", akey);
      // cout<< error;
      const char *errormsg = &error[0];
      throw std::runtime_error(error);
    }
  }
  unsigned int nodekey = key;
  Node *newNode = new Node(cargo, nodekey);
  newNode->link = node->link;
  node->link = newNode;
  key++;
  count++;
  return nodekey;
}

nodedata LinkedList::getnode()
{
  if (head == NULL)
  {
    const char *errormsg = "Warning: accessing empty list";
    throw std::runtime_error(errormsg);
  }
  Node *node = head;
  head = node->link;
  const nodedata cargo = node->cargo;
  count--;
  delete node;
  return cargo;
}

nodedata LinkedList::getnodebykey(unsigned int akey)
{
  if (head == NULL)
  {
    const char *errormsg = "Warning: accessing empty list";
    throw std::runtime_error(errormsg);
  }
  Node *node = head;
  Node **previous = &head; // bug
  while (node->key != akey)
  {
    previous = &(node->link);
    node = node->link;
    if (node == NULL)
    {
      const char *errormsg = "Warning: When getting node by key, there is no keys satisfied k = ";
      cout << errormsg << akey << endl;
      return 0;
    }
  }
  *previous = node->link;
  nodedata cargo = node->cargo;
  count--;
  delete node;
  return cargo;
}

void LinkedList::remove(unsigned int akey)
{
  nodedata cargo = getnodebykey(akey);
}

unsigned int kgen1(const unsigned int k)
{
  unsigned int n = (k * (k + 1)) / 2;
  return n;
}

unsigned int kgen2(const unsigned int k)
{
  if (k == 0)
    return 2;
  double nbang = tgamma((double)(k + 1));
  unsigned int xx = nbang + 0.01;
  unsigned int n = ((xx % (k + 1)) / k) * (k - 1) + 2;
  return n;
}

int main(int argc, char *argv[])
{
  //const unsigned int listSize = atoi(argv[1]);

  const unsigned int listSize = 15;

  LinkedList ll;

  unsigned int keys[listSize];

  for (unsigned int k = 0; k <= listSize; k++)
    keys[k] = ll.insert(2 * k + 1);

  for (unsigned int i = 1; i < 5; i++)
  {
    const unsigned int key = kgen1(i);
    nodedata thisnode = ll.getnodebykey(key);
  }
  for (unsigned int i = 1; i < 5; i++)
  {
    const unsigned int key = kgen2(i);
    nodedata thisnode = ll.getnodebykey(key);
  }

  unsigned int finished = 0;
  ll.printall();
  // Question (2)
  if (argc != 3)
  {
    printf("usage: linkedlist key cargo\n");
    return EXIT_FAILURE;
  }
  try
  {
    unsigned int key = atoi(argv[1]);
    unsigned int cargo = atoi(argv[1]);
    ll.insertafterkey(cargo, key);
  }
  catch(std::runtime_error& e)
  {
    cout << e.what() << "\n";
  }
  ll.printall();
  return EXIT_SUCCESS;
}
