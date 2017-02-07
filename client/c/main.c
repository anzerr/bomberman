#include "core/header.h"

t_core *initCore() {
    t_core *core;

    if ((core = malloc(sizeof(t_core))) == NULL)
        return (NULL);
    core->cmd = NULL;
    core->running = 1;
    initCmd(core);

    return (core);
}

int main(int argc, char **argv) {
    t_core *core;
    char *ch;
    char buffer[4096];
    int skip;

    core = initCore();
    if ((core->sockfd = connectSocket(argc, argv)) >= 0) {
        my_putstr("successfully connected.\n");
        skip = 0;
        while (core->running) {
            if (!skip) {
                my_memset(buffer, 0, sizeof(buffer));
                recv(core->sockfd, buffer, sizeof(buffer), 0);
                ch = my_strdup(buffer);
                runGamePacket(core, ch);
                free(ch);
            }

            if (core->running) {
                ch = readLine();
                skip = !runCmd(ch, core);
                free(ch);
            }
        }
        close(core->sockfd);
        core->sockfd = 0;
    }

    return (core->sockfd);
}
