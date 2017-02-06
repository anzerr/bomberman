#include "core/header.h"

t_core *initCore(int argc, char **argv) {
    t_core *core;
    t_game *game;

    if ((core = malloc(sizeof(t_core))) == NULL)
        return (NULL);

    core->running = 1;
    core->debug = (getParam(argc, argv, "-v") != NULL) ? 1 : 0;
    core->logPath = (getParam(argc, argv, "--log")) ? getParam(argc, argv, "--log") : "debug.log";
    core->size = (getParam(argc, argv, "--size")) ? my_getnbr(getParam(argc, argv, "--size")) : 10;
    core->start = getMs();

    if ((game = initGame(core)) == NULL)
        return (NULL);

    core->game = game;

    if (initLogs(core) < 0)
        return (NULL);

    return (core);
}

int listenClient(t_core *core) {
    int i, message, max_sd, sd, c, socket;
    struct sockaddr_in address;
	fd_set readfds;
	char *request;

    if ((request = malloc(sizeof(char) * REQUEST_SIZE)) == NULL)
        return (-1);

    put(core, "waiting for clients\n");
    while (core->running) {
        FD_ZERO(&readfds);
        FD_SET(core->sockfd, &readfds);
        max_sd = core->sockfd;
	    put(core, "\n---\nadd master socket\n");

        i = 0;
        while (i < MAX_PLAYER) {
            if (core->game->players[i] != NULL && core->game->players[i]->socket > 0) {
                sd = core->game->players[i]->socket;
                FD_SET(sd, &readfds);
	            put(core, "add client socket\n");
                if (max_sd < sd) {
                    max_sd = sd;
                }
            } else {
	            put(core, "empty client skip\n");
	        }
            i += 1;
        }

        message = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if (message < 0) {
	        put(core, "select failed\n");
            return (-1);
        }

	    put(core, "got select\n");
        if (FD_ISSET(core->sockfd, &readfds)) {
	        put(core, "accept socket\n");
	        c = sizeof(struct sockaddr_in);
            if ((socket = accept(core->sockfd, (struct sockaddr *)&address, (socklen_t *)&c)) < 0) {
	            put(core, "client connected failed to accept connection\n");
                return (-1);
            }

            put(core, "new user connected\n");
            put(core, inet_ntoa(address.sin_addr));
            put(core, " ip addres for client\n");
            if (initClient(core, socket) == NULL) {
                put(core, "failed to add user\n");
            } else {
                put(core, "user added into slot\n");
                sendGameInfo(core, socket);
            }
        }

        i = 0;
        while (i < MAX_PLAYER) {
            if (core->game->players[i] != NULL && FD_ISSET(core->game->players[i]->socket, &readfds)) {
                if ((c = getPackage(core->game->players[i]->socket, request)) <= 0) {
                    disconnectClient(core, i);
                    break;
                } else {
                    gameAction(core, i, request);
                }
            }
            i += 1;
        }
    }

    return (0);
}

int main(int argc, char **argv) {
    t_core *core;
    int code;
    struct sockaddr_in servaddr;

    srand(time(NULL));

    if (getParam(argc, argv, "--port") && (core = initCore(argc, argv)) != NULL) {
        if ((core->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
             put(core, "ERROR opening socket\n");
            return (0);
        }

        my_memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(my_getnbr(getParam(argc, argv, "--port")));

        if (bind(core->sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
            put(core, "ERROR on binding\n");
            return (0);
        }

        listen(core->sockfd, 4);
        code = listenClient(core);
        close(core->sockfd);
        closeLogs(core);
        return (code);
    } else {
        my_putstr("missing arguments\n");
        return (1);
    }
}
