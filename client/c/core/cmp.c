#include "header.h"

int cmpcommand(t_command *node, char *str)
{
  int l;

  l = my_strlen(node->command);
  return (my_strncmp(node->command, str, l));
}
