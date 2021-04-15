/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** handle_inputs
*/

#include "my_ftp.h"

static int handle_input(server_t *server, client_t *client);
static bool client_disconnected(const ssize_t read_bytes);
static void clear_client(server_t *server, client_t *client);

int handle_inputs(server_t *server)
{
    for (client_t *client = server->client ; client ; client = client->next)
        if (FD_ISSET(client->fd, &(server->read_fds)))
            handle_input(server, client);
    return 0;
}

static int handle_input(server_t *server, client_t *client)
{
    ssize_t bytes = 0;
    char buf[BUF_SIZE] = "\0";

    // TODO: read one by one
    bytes = read(client->fd, buf, BUF_SIZE);
    FD_CLR(client->fd, &(server->read_fds));
    if (bytes == -1) {
        handle_err_int("read");
    } else if (client_disconnected(bytes)) {
        clear_client(server, client);
    } else {
        buf[strlen(buf) - 1] = 0;
        printf("Received: [%s]\n", buf);
        handle_cmd(server, client, buf);
    }
    return 0;
}

static bool client_disconnected(const ssize_t bytes_read)
{
    return bytes_read == 0;
}

static void clear_client(server_t *server, client_t *client)
{
    client_t *previous = NULL;

    fprintf(stderr, "Disconnection from %s:%d\n",
            inet_ntoa(client->addr.sin_addr), ntohs(client->addr.sin_port));
    FD_CLR(client->fd, &(server->active_fds));
    if (server->client == client) {
        server->client = server->client->next;
    } else {
        previous = server->client;
        while (previous->next != client)
            previous = previous->next;
        previous->next = previous->next->next;
    }
    client_destroy(client);
}