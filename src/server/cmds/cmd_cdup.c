/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_cdup
*/

#include "my_ftp.h"
#include "my.h"
#include "file_reading.h"

static int change_dir(const char *root_dir);

reply_code cmd_cdup(server_t *server, client_t *client, char *arg)
{
    reply_code code = 0;

    (void)arg;
    if (change_dir(server->root_dir) == -1) {
        code = RPL_FILE_UNAVAILABLE_NO_ACCESS;
        send_reply(client->sock, code, "Failed to change directory.");
        return code;
    }
    code = RPL_FILE_ACTION_COMPLETED;
    send_reply(client->sock, code, "Directory successfully changed.");
    return code;
}

static int change_dir(const char *root_dir)
{
    char *cwd = getcwd(NULL, 0);
    int status = 0;

    if (strcmp(root_dir, cwd) == 0)
        status = -1;
    else
        status = chdir("..");
    free(cwd);
    return status;
}