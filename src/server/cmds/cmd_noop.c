/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_noop
*/

#include "my_ftp.h"
#include "cmds.h"

reply_code cmd_noop(server_t *server, client_t *client, char *arg)
{
    reply_code code = RPL_CMD_OK;

    (void)server;
    (void)arg;
    send_reply(client->fd, code, "NOOP ok.");
    return code;
}