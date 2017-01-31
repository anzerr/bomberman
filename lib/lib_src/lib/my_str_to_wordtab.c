/*
** my_str_to_wordtab.c for my_str_to_wordtab in /home/anzer_r/project/day07/anzer_r/my_str_to_wordtab
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Tue Apr  7 12:24:32 2015 ANZER ryan
** Last update Thu Apr  9 09:05:46 2015 ANZER ryan
*/
#include <stdlib.h>

int my_isalphanum(char c)
{
  int num;
  int alpha;
  num = (c >= 48 && c <= 57);
  alpha = ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
  return (num || alpha);
}

int my_getwordsize(char *str, int n)
{
  int i;
  int start;
  int word;
  int v;
  i = (start = (word = (v = 0)));
  while (str[(i = i + 1) - 1] != '\0' && (word <= n || n == -1))
    {
      if (my_isalphanum(str[i - 1]))
	  v = 1;
      else
        {
          if (v == 1)
            {
              if (word == n)
                return (start);
              word = word + 1;
              v = 0;
            }
	  start = i;
        }
    }
  return ((n == -1) ? word + ((start != (i - 1)) ? 1 : 0) : start);
}

char **my_str_to_wordtab(char *str)
{
  char **out;
  int word;
  int i;
  int v;
  int start;
  out = malloc(((word = my_getwordsize(str, -1)) + 1) * sizeof(char*));
  i = 0;
  while (i < word)
    {
      v = (start = my_getwordsize(str, i));
      while (my_isalphanum(str[(v = v + 1) - 1]));
      out[i] = malloc(((v - start) + 1) * sizeof(char));
      v = start;
      while (my_isalphanum(str[(v = v + 1) - 1]))
	  out[i][(v - start) - 1] = str[v - 1];
      out[i][(v - start) - 1] = '\0';
      i = i + 1;
    }
  out[word] = malloc(1 * sizeof(char));
  out[word] = NULL;
  return (out);
}
