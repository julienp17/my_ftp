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

    if (name == NULL)
        return 0; // no input
    arg = strtok(NULL, " ");
    if (arg != NULL && strtok(NULL, " ") != NULL)
        return -1; // extra token
    cmd = get_cmd(server->cmds, name);
    if (cmd == NULL) {
        // invalid command
        return -1;
    }
    printf("Command name = [%s], descr = [%s]\n", cmd->name, cmd->descr);
    free(cmd);
    return 0;
}