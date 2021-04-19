/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** handle_data_cmd
*/

#include "my_ftp.h"

static int fork_data_transfer(server_t *server, client_t *client,
                                cmd_t *cmd, char *arg);

reply_code handle_data_cmd(server_t *server, client_t *client,
                            cmd_t *cmd, char *arg)
{
    reply_code code = 0;

    if (server->mode == NONE) {
        code = RPL_CANNOT_OPEN_DATA_CONNECTION;
        send_reply(client->fd, code, "Use PORT or PASV first.");
    }
    (void)cmd;
    (void)arg;
    (void)fork_data_transfer;
    return code;
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