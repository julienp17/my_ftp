/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmds
*/

#ifndef CMDS_H_
#define CMDS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "client.h"

#define handle_err_null(msg) \
    do { perror(msg); return NULL; } while (0)

typedef enum reply_code {
    RPL_SERVICE_WAIT = 120,
    RPL_TRANSFER_STARTING = 125,
    RPL_FILE_READY = 150,
    RPL_CMD_OK = 200,
    RPL_HELP_MSG = 214,
    RPL_SERVICE_READY = 220,
    RPL_SERVICE_CLOSING = 221,
    RPL_FILE_ACTION_SUCCESSFUL = 226,
    RPL_PASSIVE_MODE = 227,
    RPL_LOGGED_IN = 230,
    RPL_FILE_ACTION_COMPLETED = 250,
    RPL_PATHNAME_CREATED = 257,
    RPL_USERNAME_OK = 331,
    RPL_NEED_ACCOUNT = 332,
    RPL_BAD_SEQUENCE = 503,
    RPL_UNKNOWN_COMMAND = 500,
    RPL_NOT_LOGGED_IN = 530
} reply_code;

typedef struct server server_t;
typedef reply_code (*cmd_func)(server_t *server, client_t *client, char *arg);

typedef struct command {
    char *name;
    char *descr;
    cmd_func func;
} cmd_t;

cmd_t **get_cmds(void);
cmd_t *get_cmd(cmd_t **commands, const char *cmd_name);
reply_code cmd_user(server_t *server, client_t *client, char *arg);
reply_code cmd_pass(server_t *server, client_t *client, char *arg);
reply_code cmd_quit(server_t *server, client_t *client, char *arg);
reply_code  cmd_pwd(server_t *server, client_t *client, char *arg);
reply_code cmd_help(server_t *server, client_t *client, char *arg);
reply_code cmd_noop(server_t *server, client_t *client, char *arg);

#endif /* !CMDS_H_ */
