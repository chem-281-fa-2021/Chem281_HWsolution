#include <stdexcept>
#include <hw1.1.h>

unsigned int masks5[] = {0xFFFF, 0xFF, 0xF, 0x3, 0x1 };


unsigned int findLSB(unsigned int var)
{
  if (var==0) throw std::runtime_error("invalid parameter - should not be 0");
  unsigned int flag = 0;
  unsigned short pos=0;
  unsigned short magic=16; 
  for (unsigned int pos=0; pos<5; pos++)
    {
    if (!(var&masks5[pos])) //1.  &00001111
      {
      flag |=magic; // flag becomes 000 -> 100 -> 110 -> 111
      var>>=magic; // shift 4, 2, 1 number
      }
    magic>>=1; //magic   100 -> 10 -> 1
    }
  unsigned int lsb = (flag&16)+(flag&8)+(flag&4)+(flag&2)+(flag&1);  // if flag = ABC,  (flag&4) = A00
  return lsb;
}