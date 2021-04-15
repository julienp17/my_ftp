/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** accept_client
*/

#include "my_ftp.h"

int accept_client(server_t *server)
{
    client_t *client = client_create();
    socklen_t len = sizeof(addr_t);

    client->fd = accept(server->fd, (struct sockaddr *) &(client->addr), &len);
    if (client->fd == -1)
        handle_err_int("accept");
    add_client(server, client);
    send_reply(client->fd, RPL_SERVICE_READY, "(my_ftp) Service ready");
    log_client("Connection", client);
    return 0;
}