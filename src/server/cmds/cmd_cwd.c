/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_cwd
*/

#include "my_ftp.h"
#include "my.h"
#include "file_reading.h"

static char *change_dir(const char *root_dir, client_t *client, char *arg);
static char *get_path(const char *root_dir, const char *cwd, char *arg);

reply_code cmd_cwd(server_t *server, client_t *client, char *arg)
{
    reply_code code = 0;

    if (arg == NULL || change_dir(server->root_dir, client, arg) == -1) {
        code = RPL_FILE_UNAVAILABLE_NO_ACCESS;
        send_reply(client->sock, code, "Failed to change directory.");
        return code;
    }
    code = RPL_FILE_ACTION_COMPLETED;
    send_reply(client->sock, code, "Directory successfully changed.");
    return code;
}

static char *change_dir(const char *root_dir, client_t *client, char *arg)
{
    char *cwd = get_path(root_dir, client->cwd, arg);

    if (cwd == NULL
            || !file_is_dir(cwd)
            || strncmp(root_dir, cwd, strlen(root_dir)) != 0)
        return -1;
    free(client->cwd);
    client->cwd = strdup(cwd);
    free(cwd);
    return 0;
}

static char *get_path(const char *root_dir, const char *cwd, char *arg)
{
    if (arg == NULL)
        return NULL;
    if (arg[0] == '/')
        return my_strdupcat(root_dir, arg);
    if (strncmp(arg, "./", 2) == 0)
        return my_strdupcat(cwd, arg + 1);
    if (strncmp(arg, "./", 2) == 0)
        return my_strdupcat(cwd, arg + 1);
}