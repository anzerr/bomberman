#include "../header.h"

t_client *initClient(t_core *core, int socket) {
    t_client *client;
    char *tmp;
    int i;

    i = 0;
    put(core, "create client\n");
    while (i < MAX_PLAYER) {
        if (core->game->players[i] == NULL) {
            put(core, "found free slot\n");
            if ((client = malloc(sizeof(t_client))) != NULL) {
                put(core, "malloc t_cleint\n");
                if ((client->name = malloc(sizeof(char) * 10)) != NULL) {
                    put(core, "malloc name\n");
                    client->socket = socket;
                    client->x = 0;
                    client->y = 0;
                    client->dead = 0;
                    my_memset(client->name, 0, 10);
                    my_strncpy(client->name, "anon", 9);
                    client->bombCur = 0;
                    core->game->players[i] = client;
                    tmp = gameInfoClient(core, i);
                    sendOther(core, tmp, my_strlen(tmp), i);
                    free(tmp);
                    return (core->game->players[i]);
                }
            }
        }
        i += 1;
    }
    write(socket, "CONNECT,01,KO", 15);
    close(socket);

    return (NULL);
}

void disconnectClient(t_core *core, int key) {
    char buffer[5];
    char *tmp;

    if (core->game->players[key] != NULL) {
        close(core->game->players[key]->socket);
        free(core->game->players[key]->name);
        free(core->game->players[key]);
        core->game->players[key] = NULL;
        my_memset(buffer, 0, 5);
        my_strcat(buffer, "d,");
        my_strcat(buffer, (tmp = my_nbrtostr(key)));
        free(tmp);
        sendAll(core, buffer, 5);
        put(core, "client has been closed\n");
    } else {
        put(core, "trying to disconnect invalid client\n");
    }
}

int getPackage(int socket, char *buffer) {
    int size = 0;

    memset(buffer, 0, REQUEST_SIZE);
    if ((size = read(socket, buffer, REQUEST_SIZE)) == 0) {
        return (0);
    } else {
        buffer[size] = '\0';
        return (size);
    }
}


void sendPayload(int socket, char *payload, int size) {
    write(socket, payload, size);
}

void sendOther(t_core *core, char *payload, int size, int key) {
    int i;

    i = 0;
    while (i < MAX_PLAYER) {
        if (core->game->players[i] != NULL && i != key) {
            sendPayload(core->game->players[i]->socket, payload, size);
        }
        i += 1;
    }
}

void sendAll(t_core *core, char *payload, int size) {
    sendOther(core, payload, size, -1);
}