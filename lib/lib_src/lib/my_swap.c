/*
** my_swap.c for my_swap in /home/anzer_r/project/day03/anzer_r/my_swap
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Fri Apr  3 10:36:36 2015 ANZER ryan
** Last update Fri Apr  3 10:41:20 2015 ANZER ryan
*/

void my_swap(int *a, int *b)
{
  int tmp;

  tmp = *a;
  *a = *b;
  *b = tmp;
}
