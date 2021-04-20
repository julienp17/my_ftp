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

#define CMD_USER \
    {"USER", "Specify user for authentification", &cmd_user}
#define CMD_PASS \
    {"PASS", "Specify password for authentication", &cmd_pass}
#define CMD_QUIT \
    {"QUIT", "Disconnection", &cmd_quit}
#define CMD_PWD \
    {"PWD", "Print working directory", &cmd_pwd}
#define CMD_PASV \
    {"PASV", "Enable \"passive\" mode for data transfer", &cmd_pasv}
#define CMD_PORT \
    {"PORT", "Enable \"active\" mode for data transfer", &cmd_port}
#define CMD_HELP \
    {"HELP", "List available commands", &cmd_help}
#define CMD_NOOP \
    {"NOOP", "Do nothing", &cmd_noop}
#define CMD_RETR \
    {"RETR", "Download file from server to client", &cmd_retr}

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
    RPL_SERVICE_NOT_AVAILABLE = 421,
    RPL_CANNOT_OPEN_DATA_CONNECTION = 425,
    RPL_UNKNOWN_COMMAND = 500,
    RPL_SYNTAX_ERROR = 501,
    RPL_CMD_NOT_IMPLEMENTED = 502,
    RPL_BAD_SEQUENCE = 503,
    RPL_NOT_LOGGED_IN = 530,
    RPL_FILE_UNAVAILABLE = 550
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
reply_code cmd_pasv(server_t *server, client_t *client, char *arg);
reply_code cmd_port(server_t *server, client_t *client, char *arg);
reply_code cmd_retr(server_t *server, client_t *client, char *arg);
reply_code cmd_help(server_t *server, client_t *client, char *arg);
reply_code cmd_noop(server_t *server, client_t *client, char *arg);

#endif /* !CMDS_H_ */
