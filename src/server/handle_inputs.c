/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** handle_inputs
*/

#include "my_ftp.h"

static int handle_input(server_t *server, fd_t client_fd);
static bool client_disconnected(const ssize_t read_bytes);
static void clear_client(server_t *server, fd_t client_fd);

int handle_inputs(server_t *server)
{
    for (fd_t fd = 0 ; fd < FD_SETSIZE ; fd++)
        // TODO: implement linked list
        if (FD_ISSET(fd, &(server->read_fds)) && fd != server->fd)
            handle_input(server, fd);
    return 0;
}

static int handle_input(server_t *server, fd_t client_fd)
{
    ssize_t bytes = 0;
    char buf[BUF_SIZE] = "\0";

    // TODO: read one by one
    bytes = read(client_fd, buf, BUF_SIZE);
    FD_CLR(client_fd, &(server->read_fds));
    if (bytes == -1)
        handle_err_int("read");
    else if (client_disconnected(bytes))
        clear_client(server, client_fd);
    else
        handle_cmd(server, buf);
    return 0;
}

static bool client_disconnected(const ssize_t bytes_read)
{
    return bytes_read == 0;
}

static void clear_client(server_t *server, fd_t client_fd)
{
    close(client_fd);
    FD_CLR(client_fd, &(server->active_fds));
}