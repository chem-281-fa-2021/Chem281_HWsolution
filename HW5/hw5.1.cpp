#include "linkedlist.h"
#include <stdexcept>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    printf("usage: ./hw5.1 [n] [k] [m]\n n is the number of participants\n");
    printf("We will start at k and removes the m-th participant. We will see the current paticipant as the first\n ");
    return EXIT_FAILURE;
  }
  try
  {
    const unsigned int listSize = atoi(argv[1]);
    CircledLinkedList ll;
    for (unsigned int k = 0; k < listSize; k++)
      ll.insert_atcurpoistion(k);
    ll.printall();
    unsigned int kth = atoi(argv[2]);
    unsigned int mth = atoi(argv[3]);
    if (kth < 1 || mth < 1)
    {
      const char *errormsg = "k and m must bigger than 0";
      throw std::runtime_error(errormsg);
    }
    ll.rotate_cur(kth);
    for (unsigned int k = 0; k < listSize; k++)
    {
      ll.rotate_cur(mth - 1);
      nodedata m = ll.remove_cur();
      cout << m << " ";
    }
    cout << endl;
  }
  catch (std::runtime_error &e)
  {
    cout << e.what() << "\n";
  }

  return EXIT_SUCCESS;
}
