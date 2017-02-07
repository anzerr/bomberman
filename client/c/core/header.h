/*
** header.h for header in /home/anzer_r/project/dicowesh/anzer_r/discowesh/core
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Fri Apr 17 10:38:11 2015 ANZER ryan
** Last update Sat Apr 18 12:24:36 2015 ANZER ryan
*/

#ifndef __HEADER__
#define __HEADER__

#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

#include <string.h>
#include <errno.h>

typedef struct s_list
{
  void *data;
  struct s_list *next;
} t_list;

typedef struct s_player
{
  int dead;
  int x;
  int y;
} t_player;

typedef struct s_core
{
  int sockfd;
  int running;
  int map[10][10];
  t_player player[4];

  t_list *cmd;
} t_core;

typedef struct s_command
{
  char *command;
  int (*func)();
} t_command;

char *my_nbrtostr(int n);
void runGamePacket(t_core *core, char *pack);

int up(t_core *core, char *line);
int down(t_core *core, char *line);
int left(t_core *core, char *line);
int right(t_core *core, char *line);
int bomb(t_core *core, char *line);

int my_strlen(char *str);
void my_put_nbr(int nbr);
void my_putchar(char c);
void my_putstr(char *str);
char *my_strdup(char *str);
int my_strcmp(char *s1, char *s2);
int my_strncmp(char *s1, char *s2, int max);
char *my_strncpy(char *dest, char *src, int n);
char **my_str_to_wordtab(char *str);
int my_getnbr(char *str);
char *my_strcat(char *str1, char *str2);

int connectSocket(int argc, char **argv);
char *getParam(int argc, char **argv, char *param);
void getIp(int argc, char **argv, struct in_addr *set);
void my_memset(void *buff, int put, size_t size);

char *readLine();

void initCmd(t_core *c);
void addCmd(t_list **cmd, char *com, int (*func)());
int runCmd(char *arg, t_core *c);

void my_sort_list(t_list **begin, int (*cmp)());
t_list *my_add_list(t_list **begin);
void my_remove_list(t_list **begin, void *data_ref, int (*cmp)());
void *my_find_list(t_list *begin, void *data_ref, int (*cmp)());

void messageSocket(t_core *core);

int cmpcommand(t_command *node, char *str);

int auth(t_core *core, char *line);

#endif
