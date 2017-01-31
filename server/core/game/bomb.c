#include "../header.h"

void bombExplode(t_core *core, int x, int y, int size) {
    int c, i, hit;
    char *tmp;
    t_client *player;

    if (size > 0) {
        c = core->game->map[x][y];
        if (c == 0 || c > 10) {
            return;
        }
        core->game->map[x][y] = 9;

        hit = (i = 0);
        while (i < MAX_PLAYER) {
            if (core->game->players[i] != NULL) {
                player = core->game->players[i];
                if (player->x == x && player->y == y) {
                    player->dead = 1;
                    hit += 1;
                }
            }
            i += 1;
        }
        if (hit != 0) {
            tmp = gameInfoClient(core, -1);
            sendAll(core, tmp, my_strlen(tmp));
            free(tmp);
        }

        if (x + 1 < core->size) {
            bombExplode(core, x + 1, y, size - 1);
        }
        if (y + 1 < core->size) {
            bombExplode(core, x, y + 1, size - 1);
        }
        if (x - 1 >= 0) {
            bombExplode(core, x - 1, y, size - 1);
        }
        if (y - 1 >= 0) {
            bombExplode(core, x, y - 1, size - 1);
        }
    }
}
