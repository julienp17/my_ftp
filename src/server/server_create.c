/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** server
*/

#include "my_ftp.h"
#include "file_reading.h"

static int fill_server(server_t *server, const in_port_t port,const char *path);

server_t *server_create(const in_port_t port, const char *path)
{
    server_t *server = NULL;

    if (!file_is_dir(path))
        return NULL;
    server = malloc(sizeof(server_t));
    if (server == NULL)
        handle_err_null("malloc");
    if (fill_server(server, port, path) == -1)
        return NULL;
    return server;
}

static int fill_server(server_t *server, const in_port_t port, const char *path)
{
    server->sock = create_tcp_serv(port);
    if (server->sock == -1)
        return -1;
    if (chdir(path) == -1)
        handle_err_int("chdir");
    server->root_dir = getcwd(NULL, 0);
    if (server->root_dir == NULL)
        handle_err_int("getcwd");
    server->cmds = get_cmds();
    if (server->cmds == NULL)
        return -1;
    server->data_sock = -1;
    memset(&(server->port_addr), 0, sizeof(addr_t));
    server->client = NULL;
    server->mode = NONE;
    FD_ZERO(&server->active_fds);
    FD_ZERO(&server->read_fds);
    FD_SET(server->sock, &server->active_fds);
    return 0;
}
