/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_help
*/

#include "my_ftp.h"

static void list_cmds(cmd_t **cmds);

int cmd_help(server_t *server, char *arg)
{
    cmd_t *cmd = NULL;

    if (arg == NULL) {
        list_cmds(server->cmds);
    } else {
        cmd = get_cmd(server->cmds, arg);
        if (cmd) {
            printf("\t%s: %s\n", cmd->name, cmd->descr);
        }
    }
    return 0;
}

static void list_cmds(cmd_t **cmds)
{
    printf("%d-The following commands are recognized.\n", RPL_HELP_MSG);
    for (size_t i = 0 ; cmds[i] ; i++)
        printf("    %4s: %s\n", cmds[i]->name, cmds[i]->descr);
}