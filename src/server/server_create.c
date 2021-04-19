/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** server
*/

#include "my_ftp.h"

static bool path_is_correct(const char *path);
static int fill_server(server_t *server, const in_port_t port,const char *path);
static char *get_path_with_slash(const char *path);

server_t *server_create(const in_port_t port, const char *path)
{
    server_t *server = NULL;

    if (!path_is_correct(path))
        return NULL;
    server = malloc(sizeof(server_t));
    if (server == NULL)
        handle_err_null("malloc");
    if (fill_server(server, port, path) == -1)
        return NULL;
    return server;
}

static bool path_is_correct(const char *path)
{
    struct stat file_stat;

    if (stat(path, &file_stat) == -1) {
        perror(path);
        return false;
    }
    if (!S_ISDIR(file_stat.st_mode)) {
        server_log("my_ftp: \"%s\" is not a directory\n", path);
        return false;
    }
    return true;
}

static int fill_server(server_t *server, const in_port_t port, const char *path)
{
    server->addr = create_tcp_addr(port);
    server->fd = create_tcp_sock(server->addr);
    if (server->fd == -1)
        return -1;
    server->path = get_path_with_slash(path);
    if (server->path == NULL)
        return -1;
    server->cmds = get_cmds();
    if (server->cmds == NULL)
        return -1;
    server->client = NULL;
    server->mode = NONE;
    FD_ZERO(&server->active_fds);
    FD_ZERO(&server->read_fds);
    FD_SET(server->fd, &server->active_fds);
    return 0;
}

static char *get_path_with_slash(const char *path)
{
    char *path_slash = NULL;
    size_t len = strlen(path);

    if (path[len - 1] == '/')
        return strdup(path);
    path_slash = malloc(sizeof(char) * (len + 2));
    strncpy(path_slash, path, len);
    path_slash[len] = '/';
    path_slash[len + 1] = '\0';
    return path_slash;
}
