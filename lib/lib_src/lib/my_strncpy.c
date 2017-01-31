/*
** my_strncpy.c for my_strncpy in /home/anzer_r/project/day04/anzer_r/my_strncpy
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Mon Apr  6 10:43:34 2015 ANZER ryan
** Last update Mon Apr  6 11:33:17 2015 ANZER ryan
*/

char *my_strncpy(char *dest, char *src, int n)
{
  int i;

  i = 0;
  while (src[i] != '\0' && i < n)
    {
      dest[i] = src[i];
      i = i + 1;
    }
  while (i < n)
    {
      dest[i] = '\0';
      i = i + 1;
    }
  return (dest);
}
