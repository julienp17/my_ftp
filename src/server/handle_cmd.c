/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** handle_cmds
*/

#include "cmds.h"
#include "my_ftp.h"

int handle_cmd(server_t *server, char *cmd_line)
{
    char *name = strtok(cmd_line, " "); // call my_clean_str and to_lower
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
    cmd = get_cmd(server->cmds, name);
    if (cmd == NULL) {
        fprintf(stderr, "Unknown command\n");
        return -1;
    }
    if (cmd->func == NULL)
        fprintf(stderr, "Command %s not implemented yet\n", cmd->name);
    else
        cmd->func(server, arg);
    return 0;
}