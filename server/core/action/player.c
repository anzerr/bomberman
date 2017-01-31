#include "../header.h"

int playerMove(t_core *core, int key, int xP, int yP) {
    int y, x, c, dead;
    char *tmp;

    put(core, "move getting player\n");
    if (core->game->players[key] != NULL) {
        put(core, "pos\n");
        y = core->game->players[key]->y;
        x = core->game->players[key]->x;
        dead = core->game->players[key]->dead;
        put(core, "got pos\n");
        if (y + yP < 0 || y + yP >= core->size || x + xP < 0 || x + xP >= core->size || dead) {
            put(core, "out of bound nope\n");
            return (0);
        }
        c = core->game->map[x + xP][y + yP];
        if (c < 2) {
            return (0);
        }
        put(core, "add offset\n");
        core->game->players[key]->y += yP;
        core->game->players[key]->x += xP;
        put(core, "get player info\n");
        tmp = gameInfoClient(core, key);
        put(core, "sending data\n");
        sendAll(core, tmp, my_strlen(tmp));
        put(core, "sent data\n");
        free(tmp);
        put(core, "done free\n");
        return (1);
    }
    return (0);
}

int a_playerMoveUp(t_core *core, int key) {
    return (playerMove(core, key, 0, -1));
}

int a_playerMoveDown(t_core *core, int key) {
    return (playerMove(core, key, 0, 1));
}

int a_playerMoveLeft(t_core *core, int key) {
    return (playerMove(core, key, -1, 0));
}

int a_playerMoveRight(t_core *core, int key) {
    return (playerMove(core, key, 1, 0));
}

int a_playerPlaceBomb(t_core *core, int key) {
    //char *tmp;
    t_client *player;

    put(core, "placeing bomb\n");
    if (core->game->players[key] != NULL) {
        put(core, "got player\n");
        player = core->game->players[key];
        put(core, "getting map\n");
        if (core->game->map[player->x][player->y] == 2 && !player->dead) {
            core->game->map[player->x][player->y] = 60;
            put(core, "set map pos\n");
            /*tmp = gameInfoMap(core);
            sendAll(core, tmp, my_strlen(tmp));
            free(tmp);*/
            put(core, "bomb on the map\n");
            return (1);
        }
    }
    put(core, "bomb failed player is missing\n");
    return (0);
}
