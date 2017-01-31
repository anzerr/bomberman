/*
** my_strdup.c for my_strdup in /home/anzer_r/project/day07/anzer_r/my_strdup
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Tue Apr  7 11:22:31 2015 ANZER ryan
** Last update Wed Apr  8 17:22:01 2015 ANZER ryan
*/
#include <stdlib.h>

char *my_strdup(char *str)
{
  char *ret;
  int i;
  i = 0;
  while (str[(i = i + 1)] != '\0');
  ret = malloc((i + 1) * sizeof(char));
  i = 0;
  while (str[i] != '\0')
    {
      ret[i] = str[i];
      i = i + 1;
    }
  ret[i] = '\0';
  return (ret);
}
