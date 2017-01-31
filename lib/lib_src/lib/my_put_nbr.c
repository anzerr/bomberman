/*
** my_put_nbr.c for my_put_nbr in /home/anzer_r/project/day05/anzer_r/my_put_nbr
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Sat Apr  4 09:11:24 2015 ANZER ryan
** Last update Thu Apr 16 09:10:04 2015 ANZER ryan
*/

void my_putchar(char c);

int my_numlen(int n)
{
  return ((n < 10) ? 0 : my_numlen(n / 10) + 1);
}

int my_pow(int n, int pow)
{
  return ((n < 1) ? 1 : my_pow(n - 1, pow) * pow);
}

void my_put_nbr(int n)
{
  int pow;
  int last;
  int max;
  if (n < 0)
     my_putchar('-');
  max = (n == -2147483648) ? 1 : 0;
  n = (n < 0) ? (n + max) * -1 : n;
  pow = my_pow(my_numlen(n), 10);
  last = 0;
  while (pow >= 1)
    {
      if (pow < 10)
        n = n + max;
      my_putchar(((n / pow) - (last * 10)) + 48);
      last = n / pow;
      pow = pow / 10;
    }
}
