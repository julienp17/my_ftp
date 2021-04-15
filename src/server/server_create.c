/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** server
*/

#include "my_ftp.h"

static addr_t create_server_address(in_port_t port);
static sock_t create_server_socket(const addr_t *addr);

server_t *server_create(in_port_t port)
{
    server_t *server = malloc(sizeof(server_t));

    if (server == NULL)
        handle_err_null("malloc");
    server->addr = create_server_address(port);
    server->fd = create_server_socket(&(server->addr));
    if (server->fd == -1)
        return NULL;
    server->cmds = get_cmds();
    if (server->cmds == NULL)
        return NULL;
    server->client = NULL;
    FD_ZERO(&server->active_fds);
    FD_ZERO(&server->read_fds);
    FD_SET(server->fd, &server->active_fds);
    return server;
}

static addr_t create_server_address(in_port_t port)
{
    addr_t addr;

    memset(&addr, 0, sizeof(addr_t));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = port;
    return addr;
}

static sock_t create_server_socket(const addr_t *addr)
{
    sock_t sock = socket(AF_INET, SOCK_STREAM, 0);;

    if (sock == -1)
        handle_err_int("socket");
    if (bind(sock, (const struct sockaddr *) addr, sizeof(addr_t)) == -1)
        handle_err_int("bind");
    if (listen(sock, MAX_LISTEN) == -1)
        handle_err_int("listen");
    return sock;
}

