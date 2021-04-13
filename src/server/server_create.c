/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** server
*/

#include "my_ftp.h"

static sock_t create_socket(in_port_t port);

server_t *server_create(in_port_t port)
{
    server_t *server = malloc(sizeof(server_t));

    if (server == NULL)
        handle_err_null("malloc");
    server->is_running = false;
    server->fd = create_socket(port);
    if (server->fd == -1)
        return NULL;
    FD_ZERO(&server->active_fds);
    FD_ZERO(&server->read_fds);
    FD_SET(server->fd, &server->active_fds);
    return server;
}

static sock_t create_socket(in_port_t port)
{
    fd_t sock = 0;
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr_in);

    memset(&(addr), 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = port;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        handle_err_int("socket");
    if (bind(sock, (const struct sockaddr *) &(addr), len) == -1)
        handle_err_int("bind");
    if (listen(sock, MAX_LISTEN) == -1)
        handle_err_int("listen");
    return sock;
}

