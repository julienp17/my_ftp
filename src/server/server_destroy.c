/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** server_destroy
*/

#include "my_ftp.h"

void server_destroy(server_t *server)
{
    for (size_t i = 0 ; server->cmds[i] ; i++)
        free(server->cmds[i]);
    free(server->cmds);
    close(server->fd);
    free(server);
}