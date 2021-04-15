/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_pass
*/

#include "my_ftp.h"

static reply_code decide_login(client_t *client);

reply_code cmd_pass(server_t *server, client_t *client, char *arg)
{
    reply_code code = 0;

    (void)server;
    (void)arg;
    if (client->auth == NOT_LOGGED_IN) {
        code = RPL_BAD_SEQUENCE;
        send_reply(client->fd, code, "Login with USER first.");
    } else if (client->auth == LOGGED_IN) {
        code = RPL_LOGGED_IN;
        send_reply(client->fd, code, "Already logged in.");
    } else {
        code = decide_login(client);
    }
    return code;
}

static reply_code decide_login(client_t *client)
{
    reply_code code = 0;

    if (strcmp(client->username, DEFAULT_USER) == 0) {
        code = RPL_LOGGED_IN;
        client->auth = LOGGED_IN;
        send_reply(client->fd, code, "Login succesful.");
    } else {
        free(client->username);
        client->username = NULL;
        client->auth = NOT_LOGGED_IN;
        code = RPL_NOT_LOGGED_IN;
        send_reply(client->fd, code, "Login incorrect.");
    }
    return code;
}