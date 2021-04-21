/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** get_cmds
*/

#include "cmds.h"

static cmd_t **fill_cmds(const cmd_t *static_tab);

cmd_t **get_cmds(void)
{
    cmd_t static_tab[] = {
        {"USER", "Specify user for authentification", &cmd_user},
        {"PASS", "Specify password for authentication", &cmd_pass},
        {"HELP", "List available commands", &cmd_help},
        {"QUIT", "Disconnection", &cmd_quit},
        {"CWD", "Change working directory", &cmd_cwd},
        {"CDUP", "Change working directory to parent directory", &cmd_cdup},
        {"PWD", "Print working directory", &cmd_pwd},
        {"PASV", "Enable \"passive\" mode for data transfer", &cmd_pasv},
        {"PORT", "Enable \"active\" mode for data transfer", &cmd_port},
        {"NOOP", "Do nothing", &cmd_noop},
        {"LIST", "List files in the current working directory", &cmd_list},
        {"RETR", "Download file from server to client", &cmd_retr},
        {"STOR", "Upload file from client to server", NULL},
        {"DELE", "Delete file on the server", &cmd_dele},
        {NULL, NULL, NULL}
    };

    return fill_cmds(static_tab);
}

static cmd_t **fill_cmds(const cmd_t *static_tab)
{
    size_t nb_commands = 0;
    cmd_t **cmds = NULL;

    while (static_tab[nb_commands++].name != NULL) {}
    cmds = malloc(sizeof(cmd_t *) * (nb_commands + 1));
    if (cmds == NULL)
        handle_err_null("malloc");
    for (size_t i = 0 ; static_tab[i].name != NULL ; i++) {
        cmds[i] = malloc(sizeof(cmd_t));
        if (cmds[i] == NULL)
            handle_err_null("malloc");
        cmds[i]->name = strdup(static_tab[i].name);
        cmds[i]->descr = strdup(static_tab[i].descr);
        cmds[i]->func = static_tab[i].func;
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