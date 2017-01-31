/*
** my_strcpy.c for my_strcpy in /home/anzer_r/project/day04/anzer_r/my_strcpy
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Mon Apr  6 10:09:47 2015 ANZER ryan
** Last update Mon Apr  6 15:48:45 2015 ANZER ryan
*/

char *my_strcpy(char *dest, char *src)
{
  int i;

  i = 0;
  while (src[i] != '\0')
    {
      dest[i] = src[i];
      i = i + 1;
    }
  dest[i] = '\0';

  return (dest);
}
