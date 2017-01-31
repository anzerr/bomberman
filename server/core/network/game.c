#include "../header.h"

t_game *initGame(t_core *core) {
    t_game *game;
    int i, x;

    if ((game = malloc(sizeof(t_game))) == NULL)
        return (NULL);

    game->core = core;
    i = 0;
    while (i < MAX_PLAYER) {
        game->players[i] = NULL;
        i += 1;
    }
    createMap(&game->map, core->size);
    i = 0;
    while (i < core->size) {
        x = 0;
        while (x < core->size) {
            game->map[i][x] = 1;
            x += 1;
        }
        i += 1;
    }

    return (game);
}

int createMap(int ***map, int size) {
    int i;

    i = 0;
    if ((*map = malloc(sizeof(int *) * size)) == NULL)
        return (0);
    while (i < size) {
        if (((*map)[i] = malloc(sizeof(int) * size)) == NULL)
            return (0);
        i++;
    }

    return (1);
}

int updateMap(t_core *core, int delta) {
    int i, x, changes;
    t_game *game;

    i = 0;
    changes = 0;
    game = core->game;
    while (i < core->size) {
        x = 0;
        while (x < core->size) {
            if (game->map[i][x] == 10) {
                bombExplode(core, i, x, 3);
            } else {
                if (game->map[i][x] - delta >= 1) {
                    game->map[i][x] -= delta;
                    changes += 1;
                }
                if (game->map[i][x] - 1 >= 1) {
                    game->map[i][x] -= 1;
                    changes += 1;
                }
            }
            x += 1;
        }
        i += 1;
    }
    return (changes);
}

char *gameInfoClient(t_core *core, int key) {
    char *info, *tmp;
    int size, i;
    t_client *player;

    size = 2;
    i = 0;
    while (i < MAX_PLAYER) {
        if (core->game->players[i] != NULL) {
            player = core->game->players[i];
            size += my_strlen(player->name) + ((player->y < 10) ? 2 : 3) + ((player->x < 10) ? 2 : 3) + 7;
        }
        i += 1;
    }

    if ((info = malloc(sizeof(char) * size)) == NULL)
        return (NULL);

    my_memset(info, 0, size);
    i = 0;
    while (i < MAX_PLAYER) {
       if (core->game->players[i] != NULL && (i == key || key == -1)) {
            player = core->game->players[i];
            info = my_strcat(info, "p,");
            tmp = my_nbrtostr(i);
            info = my_strcat(info, tmp);
            free(tmp);
            info = my_strcat(info, ",");
            info = my_strcat(info, player->name);
            info = my_strcat(info, ",");
            info = my_strcat(info, player->dead ? "1," : "0,");
            tmp = my_nbrtostr(player->x);
            info = my_strcat(info, tmp);
            free(tmp);
            info = my_strcat(info, ",");
            tmp = my_nbrtostr(player->y);
            info = my_strcat(info, tmp);
            free(tmp);
            info = my_strcat(info, ";");
            if (i == key) {
                break;
            }
       }
       i += 1;
    }

    return (info);
}

char *gameInfoMap(t_core *core) {
    char *info, *tmp;
    int size, i, x;

    size = 2 + ((core->size < 10)? 2 : 3) + 2;
    size += (core->size * core->size) * 2;

    if ((info = malloc(sizeof(char) * size)) == NULL)
        return (NULL);

    my_memset(info, 0, size);
    my_strcat(info, "m,");
    tmp = my_nbrtostr(core->size);
    my_strcat(info, tmp);
    free(tmp);
    my_strcat(info, ",");
    i = 0;
    while (i < core->size) {
        x = 0;
        while (x < core->size) {
            if (x != 0 || i != 0) {
                my_strcat(info, ",");
            }
            my_strcat(info, my_nbrtostr(core->game->map[i][x]));
            x += 1;
        }
        i += 1;
    }
    my_strcat(info, ";");

    return (info);
}

void sendGameInfo(t_core *core, int socket) {
    char *info, *map, *client;
    int size;

    map = gameInfoMap(core);
    client = gameInfoClient(core, -1);

    size = my_strlen(map) + my_strlen(client) + 1;
    put(core, "got the size\n");
    if ((info = malloc(sizeof(char) * size)) == NULL)
        return;

    my_memset(info, 0, size);

    my_strcat(info, client);
    free(client);
    my_strcat(info, map);
    free(map);

    sendPayload(socket, info, size);
}

void gameAction(t_core *core, int key, char *request) {
    int code, delta;
    char *tmp;

    delta = getMs() - core->start;
    if (delta >= 50) {
        int delta = updateMap(core, 1);
        if (delta != 0) {
            tmp = gameInfoMap(core);
            sendAll(core, tmp, my_strlen(tmp));
            free(tmp);
        }
        core->start = getMs();
    }

    if (request[0] == 'u') {
        code = a_playerMoveUp(core, key);
    }
    if (request[0] == 'd') {
        code = a_playerMoveDown(core, key);
    }
    if (request[0] == 'l') {
        code = a_playerMoveLeft(core, key);
    }
    if (request[0] == 'r') {
        code = a_playerMoveRight(core, key);
    }
    if (request[0] == 'b') {
        code = a_playerPlaceBomb(core, key);
    }

    if (core->game->players[key] != NULL) {
        if (code) {
            sendPayload(core->game->players[key]->socket, "OK", 2);
        } else {
            sendPayload(core->game->players[key]->socket, "KO", 2);
        }
    }
}