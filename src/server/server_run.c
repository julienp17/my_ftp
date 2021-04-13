/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** server_run
*/

#include "my_ftp.h"

static int server_loop(server_t *server);
static bool new_connection_requested(server_t *server);
static int accept_client(server_t *server);
static int handle_inputs(server_t *server);

int server_run(server_t *server)
{
    server->is_running = true;
    while (server->is_running)
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

static int accept_client(server_t *server)
{
    fd_t client_fd = 0;
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr_in);

    memset(&(addr), 0, sizeof(struct sockaddr_in));
    client_fd = accept(server->fd, (struct sockaddr *) &(addr), &len);
    if (client_fd == -1)
        handle_err_int("accept");
    printf("Connection from %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
    FD_SET(client_fd, &(server->active_fds));
    return 0;
}

static int handle_inputs(server_t *server)
{
    ssize_t bytes = 0;
    char buf[BUF_SIZE] = "\0";

    for (fd_t fd = 0 ; fd < FD_SETSIZE ; fd++) {
        if (!FD_ISSET(fd, &(server->read_fds)) || fd == server->fd)
            continue;
        bytes = read(fd, buf, BUF_SIZE);
        FD_CLR(fd, &(server->read_fds));
        if (bytes == -1) {
            handle_err_int("read");
        } else if (bytes == 0) {
            close(fd);
            FD_CLR(fd, &(server->active_fds));
        } else {
            printf("Received: %s\n", buf);
        }
    }
    return 0;
}