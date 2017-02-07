#include "header.h"

int up(t_core *core, char *line) {
    my_strlen(line);
    write(core->sockfd, "l", 2);
    return (1);
}

int down(t_core *core, char *line) {
    my_strlen(line);
    write(core->sockfd, "r", 2);
    return (1);
}

int left(t_core *core, char *line) {
    my_strlen(line);
    write(core->sockfd, "u", 2);
    return (1);
}

int right(t_core *core, char *line) {
    my_strlen(line);
    write(core->sockfd, "d", 2);
    return (1);
}

int bomb(t_core *core, char *line) {
    my_strlen(line);
    write(core->sockfd, "b", 2);
    return (1);
}
