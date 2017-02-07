#include "header.h"

int charToInt(char c) {
    return (c - 48);
}

void displayGame(t_core *core) {
    int player[10][10];
    int i, y;

    i = 0;
    while (i < 10) {
        y = 0;
        while (y < 10) {
            player[i][y] = 0;

            y += 1;
        }
        i += 1;
    }

    i = 0;
    while (i < 4) {
        player[core->player[i].y][core->player[i].x] = (core->player[i].dead)? 0 : i + 1;
        i += 1;
    }

    write(1, "\033[H\0", 5);
    write(1, "\033[2J\0", 5);
    my_putstr("-----------------------\n");
    i = 0;
    while (i < 10) {
        y = 0;
        my_putstr("|");
        while (y < 10) {
            if (player[i][y]) {
                if (player[i][y] == 1) {
                    write(1, "\033[31m", 6);
                }
                if (player[i][y] == 2) {
                    write(1, "\033[32m", 6);
                }
                if (player[i][y] == 3) {
                    write(1, "\033[33m", 6);
                }
                if (player[i][y] == 4) {
                    write(1, "\033[34m", 6);
                }
                write(1, " #\033[0m\0", 7);
            } else {
                if (core->map[i][y] == 0) {
                    my_putstr(" 0");
                } else if (core->map[i][y] == 1) {
                    my_putstr(" 1");
                } else if (core->map[i][y] == 2) {
                    my_putstr("  ");
                } else {
                    if (core->map[i][y] < 10) {
                        my_putstr(" ~");
                    }
                    if (core->map[i][y] > 10) {
                        my_putstr(" @");
                    }
                }
            }

            y += 1;
        }
        my_putstr(" |\n");
        i += 1;
    }
    my_putstr("-----------------------\n");
}

void runGamePacket(t_core *core, char *pack) {
    char buffer[4096], tmp[10];
    int i, x, y, t, p;

    my_memset(buffer, 0, 4096);
    i = (x = 0);
    while (pack[i - 1] != '\0' || (i == 0 && pack[i] != '\0')) {
        if (pack[i] == ';' || pack[i] == '\0') {
            if (buffer[0] == 'p') {
                y = charToInt(buffer[2]);
                core->player[y].dead = charToInt(buffer[9]);
                core->player[y].y = charToInt(buffer[11]);
                core->player[y].x = charToInt(buffer[13]);
            }
            if (buffer[0] == 'm') {
                y = 5;
                p = (t = 0);
                my_memset(tmp, 0, 10);
                while (buffer[y - 1] != '\0') {
                    if (buffer[y] == ',' || buffer[y] == '\0') {
                        core->map[p / 10][p % 10] = my_getnbr(tmp);
                        my_memset(tmp, 0, 10);
                        p += 1;
                        t = 0;
                    } else {
                        tmp[t] = buffer[y];
                        t += 1;
                    }
                    y += 1;
                }
            }
            if (buffer[0] == 'e') {
                my_putstr("closing someone won lol\n");
                core->running = 0;
                break;
            }

            my_memset(buffer, 0, 4096);
            x = 0;
        } else {
            buffer[x] = pack[i];
            x += 1;
        }
        i += 1;
    }
    if (core->running) {
        displayGame(core);
    }
}
