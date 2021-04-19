/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** client_destroy
*/

#include "my_ftp.h"

void client_destroy(client_t *client)
{
    if (client->username != NULL)
        free(client->username);
    if (client->fd != -1)
        close(client->fd);
    if (client->data_fd != -1)
        close(client->fd);
    free(client);
}