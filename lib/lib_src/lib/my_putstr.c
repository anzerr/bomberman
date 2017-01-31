/*
** my_putstr.c for my_putchar in /home/anzer_r/project/day03/anzer_r/my_putstr
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Fri Apr  3 09:04:01 2015 ANZER ryan
** Last update Thu Apr 16 09:10:31 2015 ANZER ryan
*/

void my_putchar(char c);

void my_putstr(char *str)
{
  char *tmp;

  tmp = str;
  while (*tmp != '\0')
    {
      my_putchar(*tmp);
      tmp = tmp + 1;
    }
}
