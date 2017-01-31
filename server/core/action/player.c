#include "../header.h"

int playerMove(t_core *core, int key, int xP, int yP) {
    int y, x;
    char *tmp;

    if (core->game->players[key] != NULL) {
        y = core->game->players[key]->y;
        x = core->game->players[key]->x;
        if (y + yP < 0 || y + yP >= core->size || x + xP < 0 || x + xP >= core->size) {
            return (0);
        }
        core->game->players[key]->y += yP;
        core->game->players[key]->x += xP;
        tmp = gameInfoClient(core, key);
        sendAll(core, tmp, my_strlen(tmp));
        free(tmp);
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
    char *tmp;
    t_client *player;

    put(core, "placeing bomb\n");
    if (core->game->players[key] != NULL) {
        player = core->game->players[key];
        if (core->game->map[player->x][player->y] == 1) {
            core->game->map[player->x][player->y] = 40;
            tmp = gameInfoMap(core);
            sendAll(core, tmp, my_strlen(tmp));
            free(tmp);
            put(core, "bomb on the map\n");
            return (1);
        }
    }
    put(core, "bomb failed player is missing\n");
    return (0);
}
