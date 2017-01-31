/*
** my_strstr.c for my_strstr in /home/anzer_r/project/day04/anzer_r/my_strstr
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Mon Apr  6 13:52:08 2015 ANZER ryan
** Last update Wed Apr  8 12:20:49 2015 ANZER ryan
*/

char *my_strstr(char *str, char *to_find)
{
  int i;
  int start;
  i = 0;
  start = 0;
  while (str[i] != '\0')
    {
      if (str[i] == to_find[start])
	{
	  start = start + 1;
	  if (to_find[start] == '\0')
	    return (&str[i - (start - 1)]);
	}
      else
	start = (str[i] == to_find[0]) ? 1 : 0;
      i = i + 1;
    }
  return ((to_find[0] == '\0') ? str : "null\0");
}
