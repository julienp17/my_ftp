/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** server
*/

#include "my_ftp.h"

static sock_t *create_server_socket(in_port_t port);

server_t *server_create(in_port_t port)
{
    server_t *server = malloc(sizeof(server_t));

    if (server == NULL)
        handle_err_null("malloc");
    server->is_running = false;
    server->sock = create_server_socket(port);
    if (server->sock == NULL)
        return NULL;
    FD_ZERO(&server->active_fds);
    FD_ZERO(&server->read_fds);
    FD_SET(server->sock->fd, &server->active_fds);
    return server;
}

static sock_t *create_server_socket(in_port_t port)
{
    sock_t *sock = malloc(sizeof(sock_t));
    socklen_t len = sizeof(struct sockaddr_in);

    if (sock == NULL)
        handle_err_null("malloc");
    memset(&(sock->addr), 0, len);
    sock->addr.sin_family = AF_INET;
    sock->addr.sin_addr.s_addr = INADDR_ANY;
    sock->addr.sin_port = port;
    sock->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->fd == -1)
        handle_err_null("socket");
    if (bind(sock->fd, (const struct sockaddr *) &(sock->addr), len) == -1)
        handle_err_null("bind");
    if (listen(sock->fd, MAX_LISTEN) == -1)
        handle_err_null("listen");
    return sock;
}

