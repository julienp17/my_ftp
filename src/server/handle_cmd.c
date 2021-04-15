/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** handle_cmds
*/

#include "my_ftp.h"
#include "my.h"

int handle_cmd(server_t *server, client_t *client, char *cmd_line)
{
    char *name = strtok(cmd_line, " ");
    char *arg = NULL;
    cmd_t *cmd = NULL;

    if (name == NULL) {
        fprintf(stderr, "No input\n");
        return 0;
    }
    arg = strtok(NULL, " ");
    if (arg != NULL && strtok(NULL, " ") != NULL) {
        fprintf(stderr, "Extra token found\n");
        return -1;
    }
    cmd = get_cmd(server->cmds, my_str_toupper(name));
    if (cmd == NULL) {
        fprintf(stderr, "Unknown command\n");
        return -1;
    }
    if (cmd->func == NULL)
        fprintf(stderr, "Command %s not implemented yet\n", cmd->name);
    else
        cmd->func(server, client, arg);
    return 0;
}