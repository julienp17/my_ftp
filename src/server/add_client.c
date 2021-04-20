/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** add_client
*/

#include "my_ftp.h"

void add_client(server_t *server, client_t *client)
{
    if (server->client == NULL) {
        server->client = client;
    } else {
        client->next = server->client;
        server->client = client;
    }
    FD_SET(client->sock, &(server->active_fds));
}