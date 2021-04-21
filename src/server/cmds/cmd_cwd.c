/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_cwd
*/

#include "my_ftp.h"
#include "my.h"
#include "file_reading.h"

static int change_dir(const char *root_dir, char *arg);

reply_code cmd_cwd(server_t *server, client_t *client, char *arg)
{
    reply_code code = 0;

    if (arg == NULL || change_dir(server->root_dir, arg) == -1) {
        code = RPL_FILE_UNAVAILABLE_NO_ACCESS;
        send_reply(client->sock, code, "Failed to change directory.");
        return code;
    }
    code = RPL_FILE_ACTION_COMPLETED;
    send_reply(client->sock, code, "Directory successfully changed.");
    return code;
}

static int change_dir(const char *root_dir, char *arg)
{
    char *prev_cwd = getcwd(NULL, 0);
    char *cwd = NULL;
    int status = 0;

    if (arg[0] == '/')
        arg = my_strdupcat(root_dir, arg);
    status = chdir(arg);
    cwd = getcwd(NULL, 0);
    if (strncmp(root_dir, cwd, strlen(root_dir)) != 0) {
        chdir(prev_cwd);
        status = -1;
    }
    free(cwd);
    return status;
}