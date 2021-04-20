/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_pwd
*/

#include "my_ftp.h"

reply_code cmd_pwd(server_t *server, client_t *client, char *arg)
{
    reply_code code = RPL_PATHNAME_CREATED;

    (void)arg;
    send_str(client->sock, "%d \"%s\"", code, server->path);
    return code;
}