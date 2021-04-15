/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** handle_cmds
*/

#include "my_ftp.h"
#include "my.h"

static bool is_login_cmd(const char *cmd_name);
static bool is_data_transfer_cmd(const char *cmd_name);
static int fork_data_transfer(server_t *server, client_t *client,
                                cmd_t *cmd, char *arg);

reply_code handle_cmd(server_t *server, client_t *client, cmd_t *cmd, char *arg)
{
    reply_code code = 0;

    if (cmd->func == NULL) { // temporary
        server_log("Command %s not implemented yet\n", cmd->name);
        return -1;
    }
    if (client->auth != LOGGED_IN && !is_login_cmd(cmd->name)) {
        code = RPL_NOT_LOGGED_IN;
        send_reply(client->fd, code, "Please login with USER and PASS.");
        return code;
    }
    if (is_data_transfer_cmd(cmd->name))
        return fork_data_transfer(server, client, cmd, arg);
    code = cmd->func(server, client, arg);
    return code;
}

static bool is_login_cmd(const char *cmd_name)
{
    return (
        strcmp(cmd_name, "USER") == 0
        || strcmp(cmd_name, "PASS") == 0
        || strcmp(cmd_name, "HELP") == 0
    );
}

static bool is_data_transfer_cmd(const char *cmd_name)
{
    return (
        strcmp(cmd_name, "RETR") == 0
        || strcmp(cmd_name, "STOR") == 0
        || strcmp(cmd_name, "LIST") == 0
    );
}

static int fork_data_transfer(server_t *server, client_t *client,
                            cmd_t *cmd, char *arg)
{
    pid_t pid = fork();

    if (pid == -1)
        handle_err_int("fork");
    else if (pid == 0)
        _exit(cmd->func(server, client, arg));
    return 0;
}