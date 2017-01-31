
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
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>

#define MAX_PLAYER 4
#define REQUEST_SIZE 1024

struct s_client;
struct s_core;
struct s_game;

typedef struct s_list
{
  void *data;
  struct s_list *next;
} t_list;


typedef struct s_client
{
  int socket;
  char *name;
  int x;
  int y;
  int dead;
  int bombCur;
} t_client;

typedef struct s_core
{
  int sockfd;
  int running;
  int debug;
  char *logPath;
  int size;
  int logHandle;
  int start;
  struct s_game *game;
} t_core;

typedef struct s_game
{
  struct s_client *players[MAX_PLAYER];
  int **map;
  struct s_core *core;
} t_game;

t_client *initClient(t_core *core, int socket);
t_game *initGame(t_core *core);
void sendGameInfo(t_core *core, int socket);
int getPackage(int socket, char *req);
void disconnectClient(t_core *core, int key);
void gameAction(t_core *core, int key, char *request);
int createMap(int ***map, int size);

char *gameInfoClient(t_core *core, int key);
char *gameInfoMap(t_core *core);
void sendGameInfo(t_core *core, int socket);

int updateMap(t_core *core, int delta);

void bombExplode(t_core *core, int x, int y, int size);

void sendPayload(int socket, char *payload, int size);
void sendAll(t_core *core, char *payload, int size);
void sendOther(t_core *core, char *payload, int size, int key);

int playerMove(t_core *core, int key, int xP, int yP);
int a_playerMoveUp(t_core *core, int key);
int a_playerMoveDown(t_core *core, int key);
int a_playerMoveLeft(t_core *core, int key);
int a_playerMoveRight(t_core *core, int key);
int a_playerPlaceBomb(t_core *core, int key);

int getMs();
int close(int fd);

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

void my_sort_list(t_list **begin, int (*cmp)());
t_list *my_add_list(t_list **begin);
void my_remove_list(t_list **begin, void *data_ref, int (*cmp)());
void *my_find_list(t_list *begin, void *data_ref, int (*cmp)());
void my_add_list_to_list(t_list **begin1,t_list *begin2);

char *my_strstr(char *str, char *to_find);
char *my_strcpy(char *dest, char *src);

void my_memset(void *buff, int put, size_t size);
char *getParam(int argc, char **argv, char *param);

int initLogs(t_core *core);
void closeLogs(t_core *core);
int error(t_core *core, char *str);
int put(t_core *core, char *str);
int putnbr(t_core *core, int n);

int my_numlen(int n);
int my_pow(int n, int pow);
char *my_nbrtostr(int n);
#endif
