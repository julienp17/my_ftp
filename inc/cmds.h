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

#define handle_err_null(msg) \
    do { perror(msg); return NULL; } while (0)

typedef int fd_t;
typedef struct server server_t;
typedef int (*cmd_func)(server_t *server, fd_t client_fd, char *arg);

typedef struct command {
    char *name;
    char *descr;
    cmd_func func;
} cmd_t;

cmd_t **get_cmds(void);
cmd_t *get_cmd(cmd_t **commands, const char *cmd_name);
int cmd_help(server_t *server, fd_t client_fd, char *arg);

#endif /* !CMDS_H_ */
