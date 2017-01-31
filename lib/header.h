
#ifndef __HEADER_LIB__
#define __HEADER_LIB__

#include <stdlib.h>

typedef struct s_list
{
  void *data;
  struct s_list *next;
} t_list;

void my_memset(void *buff, int put, size_t size);
int my_numlen(int n);
int my_pow(int n, int pow);
#endif
