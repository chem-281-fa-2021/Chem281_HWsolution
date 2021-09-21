#include <stdio.h>
#include <stdlib.h>
#include <cstring>

void addnumber(char*list, unsigned int& listSize, const unsigned int maxdigits,
	       unsigned int position, const unsigned int target, const unsigned int root)
{
  if (target == 0)
    {
    printf("%s\n", list);
    return;
    }
  const unsigned int endloop = target > root ? root : target;
  for(unsigned int k=0; k<endloop; k++)
    {
    const unsigned int nextroot = endloop-k;
    // extra space: 1 for the space after the number + 1 for \0
    if (strlen(list)+maxdigits+2 > listSize) throw "resize required";
    sprintf(list+position, "%d ", nextroot);
    const unsigned int newposition = strlen(list);
    addnumber(list, listSize, maxdigits, newposition, target-nextroot, nextroot);
    }
}

unsigned int countdigits(unsigned int n)
{
  if (n<10) return 1;
  return 1+countdigits(n/10);
}

int main(int argc, char* argv[])
{
  if (argc != 2)
    {
    printf("usage: hw2.2  number\n");
    return EXIT_FAILURE;  
    }
  unsigned int target = atoi(argv[1]);

  const float resizefactor = 1.5;
  unsigned int listsize = 5;
  char* list = new char[listsize];

  const unsigned int maxdigits = countdigits(target);
  bool doloop = false;
  do
    {
    doloop = false;
    try
      {
      addnumber(list, listsize , maxdigits, 0, target, target);
      }
    catch (const char* message)
      {
      listsize = listsize * resizefactor;
      char* expandedlist = new char[listsize];
      strcpy(expandedlist, list);
      delete[] list;
      list = expandedlist;
      printf("WARNING: %s new size %d\n", message, listsize);
      doloop = true;
      }
    } while(doloop);
  delete list;
  return EXIT_SUCCESS;
}
