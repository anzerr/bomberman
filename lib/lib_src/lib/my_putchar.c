/*
** my_putchar.c for my_putchar in /home/anzer_r
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Wed Apr  1 14:50:45 2015 ANZER ryan
** Last update Wed Apr  1 15:23:27 2015 ANZER ryan
*/
#include <unistd.h>

void my_putchar(char c)
{
  write(1, &c, 1);
}
