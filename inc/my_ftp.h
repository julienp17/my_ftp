/*
** EPITECH PROJECT, 2021
** my_ftp [WSL: Ubuntu-20.04]
** File description:
** my_ftp
*/

#ifndef MY_FTP_H_
#define MY_FTP_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_LISTEN      5
#define MAX_MSG_LEN     1024
#define BUF_SIZE        1024
#define handle_err_int(msg) \
    do { perror(msg); return -1; } while (0)
#define handle_err_null(msg) \
    do { perror(msg); return NULL; } while (0)

typedef int fd_t;
typedef fd_t sock_t;

enum ftp_reply_code {
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
    RPL_NEED_ACCOUNT = 332
};

typedef struct server {
    bool is_running;
    fd_t fd;
    fd_set active_fds;
    fd_set read_fds;
} server_t;

server_t *server_create(in_port_t port);
int server_run(server_t *server);
void server_destroy(server_t *server);


#endif /* !MY_FTP_H_ */
