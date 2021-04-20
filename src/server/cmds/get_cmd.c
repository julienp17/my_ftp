/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** get_cmds
*/

#include "cmds.h"

cmd_t **get_cmds(void)
{
    cmd_t cmds_tab[] = {
        CMD_USER, CMD_PASS,
        {"CWD", "Change working directory", NULL},
        {"CDUP", "Change working directory to parent directory", NULL},
        CMD_QUIT,
        {"DELE", "Delete file on the server", NULL},
        CMD_PWD, CMD_PASV, CMD_PORT, CMD_HELP, CMD_NOOP, CMD_RETR,
        {"STOR", "Upload file from client to server", NULL},
        {"LIST", "List files in the current working directory", NULL},
        {NULL, NULL, NULL}
    };
    size_t nb_commands = 0;
    cmd_t **cmds = NULL;

    while (cmds_tab[nb_commands++].name != NULL) {}
    cmds = malloc(sizeof(cmd_t *) * (nb_commands + 1));
    if (cmds == NULL)
        handle_err_null("malloc");
    for (size_t i = 0 ; cmds_tab[i].name != NULL ; i++) {
        cmds[i] = malloc(sizeof(cmd_t));
        if (cmds[i] == NULL)
            handle_err_null("malloc");
        cmds[i]->name = strdup(cmds_tab[i].name);
        cmds[i]->descr = strdup(cmds_tab[i].descr);
        cmds[i]->func = cmds_tab[i].func;
    }
    cmds[nb_commands] = NULL;
    return cmds;
}

cmd_t *get_cmd(cmd_t **commands, const char *cmd_name)
{
    cmd_t *cmd = NULL;

    for (int i = 0 ; commands[i] != NULL && cmd == NULL ; i++)
        if (strcmp(commands[i]->name, cmd_name) == 0)
            cmd = commands[i];
    return cmd;
}