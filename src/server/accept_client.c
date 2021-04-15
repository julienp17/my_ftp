/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** accept_client
*/

#include "my_ftp.h"

static void log_connection(const client_t *client);
static void add_client(server_t *server, client_t *client);

int accept_client(server_t *server)
{
    client_t *client = client_create();
    socklen_t len = sizeof(addr_t);

    client->fd = accept(server->fd, (struct sockaddr *) &(client->addr), &len);
    if (client->fd == -1)
        handle_err_int("accept");
    add_client(server, client);
    send_reply(client->fd, RPL_SERVICE_READY, "(my_ftp) Service ready");
    log_connection(client);
    return 0;
}

static void add_client(server_t *server, client_t *client)
{
    if (server->client == NULL) {
        server->client = client;
    } else {
        client->next = server->client;
        server->client = client;
    }
    FD_SET(client->fd, &(server->active_fds));
}

static void log_connection(const client_t *client)
{
    fprintf(stderr, "Connection from %s:%d\n",
            inet_ntoa(client->addr.sin_addr), ntohs(client->addr.sin_port));
}