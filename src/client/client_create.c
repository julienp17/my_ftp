/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** client_create
*/

#include "my_ftp.h"

client_t *client_create(void)
{
    client_t *client = malloc(sizeof(client_t));

    if (client == NULL)
        handle_err_null("malloc");
    client->fd = -1;
    memset(&(client->addr), 0, sizeof(addr_t));
    client->data_fd = -1;
    memset(&(client->data_addr), 0, sizeof(addr_t));
    client->username = NULL;
    client->auth = NOT_LOGGED_IN;
    client->next = NULL;
    return client;
}