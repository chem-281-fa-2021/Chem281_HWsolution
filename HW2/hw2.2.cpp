#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

void Fill_list(char* list_pointer, char* &new_pointer, int number, int last_number, int &left_space, int max_buffer){
  // if (number == 1)
  // {
  //   list_pointer[0] = '1';
  //   list_pointer[1] = '\n';
  //   left_space --;
  //   list_pointer = & list_pointer[2];
  //   return;
  // }
  // else{
    // char * new_pointer = list_pointer;
    char * old_pointer = new_pointer;
    int allowed_number = min(number , last_number);
    for(int i = allowed_number; i > 0; i--){
      printf("new iter: now list is\n%s \n", list_pointer);
        printf("new_pointer %s\n", new_pointer);
      old_pointer = new_pointer;
      char add_num[max_buffer];
      int n=sprintf (add_num, "%d ",i);
      // sprintf ("[%s] is a string %d chars long\n",add_num,n);
      /* using memcpy to copy string: */
      memcpy( new_pointer, &add_num, n);
        printf("after copy is  %s\n", new_pointer);
      left_space -= n;
      printf("add a number, %s, which is %d byte, left space is %d\n", add_num, n, left_space);
      new_pointer = & new_pointer[n];
      int left_number = number - i;
      if(left_number > 0){
        printf("left_number: %d, last_number: %d start new func\n", left_number, i);
        printf("before new func is  %s\n", old_pointer);
        Fill_list(list_pointer, new_pointer, left_number, i, left_space, max_buffer);
        
      }
      else{
        new_pointer[0] = '\n';
        left_space --;
        new_pointer = & new_pointer[1];
        // printf("end %s\n", old_pointer);
        printf("refresh %s\n", new_pointer);

      }
      printf("end iter %s\n", old_pointer);
        printf("end iter new %s\n", new_pointer);

    }
  // }
        printf("end func %s\n", old_pointer);
}




int main(int argc, char* argv[])
{
    if (argc !=2){
        printf("usage hw2.2 number, for example hw1.1 250\n");
        return EXIT_FAILURE;
    }
    int target = stoi(argv[1]);
    int list_size = 100;
    char * list = new char[list_size +1];
    char * new_pointer = list;
    list[list_size]= '\0';
    Fill_list(list, new_pointer, target, target,list_size, 10);
    printf("%s \n", list);

    return EXIT_SUCCESS;
}
