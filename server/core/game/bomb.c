#include "../header.h"

void bombExplode(t_core *core, int x, int y, int size) {
    if (size > 0) {
        core->game->map[x][y] = 9;
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
