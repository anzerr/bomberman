#include "header.h"

char *getParam(int argc, char **argv, char *param)
{
  int i;
  int length;

  i = 0;
  length = my_strlen(param);
  while (i < argc)
    {
      if (length == 2 && my_strlen(argv[i]) >= 2 && argv[i][1] != '-' && i != 0)
	{
	  if (my_strcmp(my_strstr(argv[i], &param[1]), "null") != 0)
	    return ("1");
	}
      else
	{
	  if (my_strcmp(argv[i], param) == 0 && i + 1 < argc)
	    return (argv[i + 1]);
	}
      i += 1;
    }
  return (NULL);
}

int getMs() {
    struct timeval tv;
    int msec = -1;

    if (gettimeofday(&tv, NULL) == 0) {
        msec = ((tv.tv_sec % 86400) * 1000 + tv.tv_usec / 1000);
    }

    return(msec);
}