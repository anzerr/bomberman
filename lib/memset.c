#include "header.h"

void my_memset(void *buff, int put, size_t size)
{
  size_t i;
  char *mem;
  
  mem = buff;
  i = 0;
  while (i < size)
    {
      mem[i] = put;
      i++;
    }
}
