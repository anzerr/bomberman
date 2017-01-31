/*
** my_strncat.c for my_strncat in /home/anzer_r/main/day04
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Mon Apr  6 12:56:58 2015 ANZER ryan
** Last update Mon Apr  6 12:57:01 2015 ANZER ryan
*/

char *my_strncat(char *str1, char *str2, int n)
{
  int i;
  int start;
  i = 0;
  start = -1;
  while (1)
    {
      if (str1[i] == '\0' && start == -1)
	start = i;
      if (start != -1)
        str1[i] = (i - start >= n) ? '\0' : str2[i - start];
      if (start != -1 && (str2[i - start] == '\0' || i - start >= n))
	break;
      i = i + 1;
    }

  return (str1);
}
