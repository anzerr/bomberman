/*
** my_getnbr.c for my_getnbr in /home/anzer_r/project/day05/anzer_r/my_getnbr
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Sat Apr  4 11:48:29 2015 ANZER ryan
** Last update Tue Apr  7 17:01:35 2015 ANZER ryan
*/

int my_getnbr(char *str)
{
  int i;
  int neg;
  int num;
  i = 0;
  neg = 1;
  while (str[i] == 45 || str[i] == 43)
    {
      neg = (str[i] == 45) ? neg * -1 : neg;
      i = i + 1;
    }
  num = 0;
  while ((str[i] >= 48 && str[i] <= 57))
    {
      if (str[i] >= 48 && str[i] <= 57)
	  num = (num * 10) + (str[i] - 48);
      i = i + 1;
    }
  return (num * neg);
}
