/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** accept_client
*/

#include "my_ftp.h"

int accept_client(server_t *server)
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