#include "header.h"

int connectSocket(int argc, char **argv)
{
  int sockfd;
  struct sockaddr_in servaddr;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < -1)
    {
      my_putstr("can't open socket.\n");
      return (-1);
    }

  my_memset(&servaddr, 0, sizeof(struct sockaddr_in));
  servaddr.sin_family = AF_INET;
  getIp(argc, argv, &servaddr.sin_addr);
  servaddr.sin_port = htons(my_getnbr(getParam(argc, argv, "--port")));
  
  if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    {
      my_putstr(strerror(errno));
      my_putstr("\n");
      return (-3);
    }
  return (sockfd);
}

void getIp(int argc, char **argv, struct in_addr *stur)
{
  struct in_addr *sin_addr;
  
  if ((sin_addr = malloc(sizeof(struct in_addr))) == NULL)
    return;
  my_memset(sin_addr, 0, sizeof(struct in_addr));
  sin_addr->s_addr = inet_addr(getParam(argc, argv, "--ip"));
  *stur = *sin_addr;
}

char *getParam(int argc, char **argv, char *param)
{
  int i;

  i = 0;
  while (i < argc)
    {
      if (my_strcmp(argv[i], param) == 0 && i + 1 < argc)
	{
	  return (argv[i + 1]);
	}
      i += 1;
    }
  return (NULL);
}

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