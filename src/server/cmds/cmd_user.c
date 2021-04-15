/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_user
*/

#include "my_ftp.h"

int cmd_user(server_t *server, client_t *client, char *arg)
{
    reply_code code = 0;

    (void)server;
    if (client->auth == LOGGED_IN) {
        code = RPL_NOT_LOGGED_IN;
        send_reply(client->fd, code, "Can't change from guest user.");
    } else {
        if (arg == NULL) {
            code = RPL_NOT_LOGGED_IN;
            send_reply(client->fd, code, "Permission denied.");
        } else {
            code = RPL_USERNAME_OK;
            client->auth = USERNAME_ENTERED;
            client->username = strdup(arg);
            send_reply(client->fd, code, "Please specify the password.");
        }
    }
    return code;
}