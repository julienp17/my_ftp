/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** handle_cmds
*/

#include "my_ftp.h"

static cmd_t *get_cmd(const char *cmd_name);

int handle_cmd(server_t *server, char *cmd_line)
{
    char *name = strtok(cmd_line, " ");
    cmd_t *cmd = NULL;

    if (name == NULL)
        return 0; // no input
    cmd = get_cmd(name);
    if (cmd == NULL) {
        // send invalid command
        return -1;
    }
    (void)server;
    printf("Command name = [%s], descr = [%s]\n", cmd->name, cmd->descr);
    return 0;
}

static cmd_t *get_cmd(const char *cmd_name)
{
    cmd_t cmds[] = {
        {"USER", NULL, "Specify user for authentification"},
        {"PASS", NULL, "Specify password for authentication"},
        {"CWD", NULL, "Change working directory"},
        {"CDUP", NULL, "Change working directory to parent directory"},
        {"QUIT", NULL, "Disconnection"},
        {"DELE", NULL, "Delete file on the server"},
        {"PWD", NULL, "Print working directory"},
        {"PASV", NULL, "Enable \"passive\" mode for data transfer"},
        {"PORT", NULL, "Enable \"active\" mode for data transfer"},
        {"HELP", NULL, "List available commands"},
        {"NOOP", NULL, "Do nothing"},
        {"RETR", NULL, "Download file from server to client"},
        {"STOR", NULL, "Upload file from client to server"},
        {"LIST", NULL, "List files in the current working directory"},
        {NULL, NULL, NULL}
    };
    cmd_t *cmd = NULL;

    for (int i = 0 ; cmds[i].name != NULL && cmd == NULL ; i++) {
        if (strcmp(cmds[i].name, cmd_name) == 0) {
            cmd = malloc(sizeof(cmd_t));
            if (cmd == NULL)
                handle_err_null("malloc");
            cmd->name = strdup(cmds[i].name);
            cmd->arg = NULL;
            cmd->descr = strdup(cmds[i].descr);
        }
    }
    return cmd;
}