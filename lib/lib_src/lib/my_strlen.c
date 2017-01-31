/*
** my_strlen.c for my_strlen in /home/anzer_r/project/day03/anzer_r/my_strlen
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Fri Apr  3 10:10:49 2015 ANZER ryan
** Last update Tue Apr  7 17:03:28 2015 ANZER ryan
*/

int my_strlen(char *str)
{
  int i;
  i = 0;
  while (str[(i = i + 1)] != '\0');
  return (i);
}
