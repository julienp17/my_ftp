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
    addr_t addr;
    socklen_t len = sizeof(addr_t);

    client->fd = accept(server->fd, (struct sockaddr *) &addr, &len);
    if (client->fd == -1)
        handle_err_int("accept");
    add_client(server, client);
    send_reply(client->fd, RPL_SERVICE_READY, "(myftp) Service ready");
    server_log_addr("Connection from", client->fd);
    return 0;
}