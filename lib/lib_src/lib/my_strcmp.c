/*
** my_strcmp.c for my_strcmp in /home/anzer_r/project/day04/anzer_r/my_strcmp
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Mon Apr  6 11:07:55 2015 ANZER ryan
** Last update Mon Apr  6 16:07:15 2015 ANZER ryan
*/

int my_strcmp(char *s1, char *s2)
{
  int i;
  i = 0;
  while (s1[i] != '\0' || s2[i] != '\0')
    {
      if (s1[i] == '\0' || s2[i] == '\0')
	return ((s1[i] == '\0') ? -1 : 1);
      if (s1[i] != s2[i])
	return ((s1[i] < s2[i]) ? -1 : 1);
      i = i + 1;
    }
  return (0);
}
