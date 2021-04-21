/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_pwd
*/

#include "my_ftp.h"
#include "my.h"

reply_code cmd_pwd(server_t *server, client_t *client, char *arg)
{
    reply_code code = RPL_PATHNAME_CREATED;
    char *cwd = NULL;

    (void)arg;
    if (strcmp(server->root_dir, client->cwd) == 0) {
        cwd = strdup("/");
    } else {
        cwd = strdup(client->cwd);
        strcpy(cwd, cwd + strlen(server->root_dir));
    }
    send_str(client->sock, "%d \"%s\" is the current directory.", code, cwd);
    free(cwd);
    return code;
}