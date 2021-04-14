/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** accept_client
*/

#include "my_ftp.h"

int accept_client(server_t *server)
{
    sock_t *client = socket_create();

    client->fd = accept(server->sock->fd, (struct sockaddr *) &(client->addr),
                        &(client->len));
    if (client->fd == -1)
        handle_err_int("accept");
    printf("Connection from %s:%d\n", inet_ntoa(client->addr.sin_addr),
                                                ntohs(client->addr.sin_port));
    FD_SET(client->fd, &(server->active_fds));
    free(client); // temporary
    return 0;
}