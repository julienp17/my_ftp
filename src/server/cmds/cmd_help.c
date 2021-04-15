/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_help
*/

#include "my_ftp.h"
#include "my.h"

static void list_cmds(fd_t client_fd, cmd_t **cmds);

reply_code cmd_help(server_t *server, client_t *client, char *arg)
{
    cmd_t *cmd = NULL;

    if (arg == NULL) {
        list_cmds(client->fd, server->cmds);
    } else {
        cmd = get_cmd(server->cmds, my_str_toupper(arg));
        if (cmd)
            send_str(client->fd, "%8s: %s", cmd->name, cmd->descr);
    }
    return RPL_HELP_MSG;
}

static void list_cmds(fd_t client_fd, cmd_t **cmds)
{
    reply_code code = RPL_HELP_MSG;

    send_reply(client_fd, code, "The following commands are recognized.");
    for (size_t i = 0 ; cmds[i] ; i++)
        send_str(client_fd, "%8s", cmds[i]->name);
}