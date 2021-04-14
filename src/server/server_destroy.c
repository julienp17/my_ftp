/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** server_destroy
*/

#include "my_ftp.h"

void server_destroy(server_t *server)
{
    close(server->sock->fd);
    free(server->sock);
    free(server);
}