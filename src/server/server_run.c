/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** server_run
*/

#include "my_ftp.h"

static int server_loop(server_t *server);
static bool new_connection_requested(server_t *server);

int server_run(server_t *server)
{
    printf("Listening on port %d...\n", ntohs(server->addr.sin_port));
    while (1)
        server_loop(server);
    return 0;
}

static int server_loop(server_t *server)
{
    int status = 0;

    server->read_fds = server->active_fds;
    if (select(FD_SETSIZE, &(server->read_fds), NULL, NULL, NULL) == -1)
        handle_err_int("select");
    if (new_connection_requested(server))
        status = accept_client(server);
    else
        status = handle_inputs(server);
    return status;
}

static bool new_connection_requested(server_t *server)
{
    return FD_ISSET(server->fd, &(server->read_fds));
}