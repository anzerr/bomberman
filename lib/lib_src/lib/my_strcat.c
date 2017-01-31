/*
** my_strcat.c for my_strcat in /home/anzer_r/project/day04/anzer_r/my_strcat
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Mon Apr  6 11:55:47 2015 ANZER ryan
** Last update Mon Apr  6 12:26:23 2015 ANZER ryan
*/

char *my_strcat(char *str1, char *str2)
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
        str1[i] = str2[i - start];
      if (start != -1 && str2[i - start] == '\0')
	break;
      i = i + 1;
    }

  return (str1);
}
