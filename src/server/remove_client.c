/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** remove_client
*/

#include "my_ftp.h"

void remove_client(server_t *server, client_t *client)
{
    client_t *previous = NULL;

    if (server->client == client) {
        server->client = server->client->next;
    } else {
        previous = server->client;
        while (previous->next != client)
            previous = previous->next;
        previous->next = previous->next->next;
    }
    FD_CLR(client->fd, &(server->active_fds));
    server_log_addr("Disconnection from", client->fd);
    client_destroy(client);
}