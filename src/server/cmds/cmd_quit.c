/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_quit
*/

#include "my_ftp.h"

reply_code cmd_quit(server_t *server, client_t *client, char *arg)
{
    reply_code code = RPL_SERVICE_CLOSING;

    (void)arg;
    send_reply(client->sock, code, "Goodbye.");
    remove_client(server, client);
    return code;
}