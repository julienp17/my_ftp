/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_noop
*/

#include "my_ftp.h"
#include "cmds.h"

int cmd_noop(server_t *server, client_t *client, char *arg)
{
    (void)server;
    (void)arg;
    send_reply(client->fd, RPL_CMD_OK, "NOOP ok.");
    return RPL_CMD_OK;
}