#include "header.h"

char *readLine()
{
  char buffer[256];
  char *a;
  char *b;
  int part;
  int bSize;
  int out;
  
  bSize = 255;
  part = 1;
  a = NULL;
  while (1)
    {
      my_memset(buffer, 0, 256);
      out = read(0, buffer, bSize);
      if ((b = malloc(sizeof(char) * ((bSize * part) + 1))) == NULL)
	return (NULL);
      my_memset(b, 0, (bSize * part) + 1);
      my_strcat(b, (a != NULL) ? a : "");
      my_strcat(b, buffer);
      b[(bSize * part)] = '\0';
      if (a != NULL) 
	free(a);
      a = b;
      if (out >= bSize)
	part += 1;
      else
	break;
    }
  return (a);
}
