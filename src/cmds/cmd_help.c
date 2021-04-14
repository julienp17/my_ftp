/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_help
*/

#include "my_ftp.h"

static void list_cmds( fd_t client_fd, cmd_t **cmds);

int cmd_help(server_t *server, fd_t client_fd, char *arg)
{
    cmd_t *cmd = NULL;

    if (arg == NULL) {
        list_cmds(client_fd, server->cmds);
    } else {
        cmd = get_cmd(server->cmds, arg);
        if (cmd)
            send_client(client_fd, "%8s: %s\n", cmd->name, cmd->descr);
    }
    return 0;
}

static void list_cmds(fd_t client_fd, cmd_t **cmds)
{
    send_reply(client_fd, RPL_HELP_MSG, "The following commands are recognized.");
    for (size_t i = 0 ; cmds[i] ; i++)
        send_client(client_fd, "%8s: %s", cmds[i]->name, cmds[i]->descr);
}