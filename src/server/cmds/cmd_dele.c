/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_dele
*/

#include "my_ftp.h"
#include "my.h"

reply_code cmd_dele(server_t *server, client_t *client, char *arg)
{
    reply_code code = 0;
    char *filename = NULL;

    (void)server;
    if (arg == NULL) {
        code = RPL_SYNTAX_ERROR;
        send_reply(client->sock, code, "No file specified to delete.");
        return code;
    }
    filename = my_strdupcat(my_strdupcat(getcwd(NULL, 0), "/"), arg);
    if (remove(filename) == -1) {
        code = RPL_FILE_UNAVAILABLE_NO_ACCESS;
        send_reply(client->sock, code, "File not found to delete.");
    } else {
        code = RPL_FILE_ACTION_COMPLETED;
        send_reply(client->sock, code, "File successfully deleted.");
    }
    return code;
}