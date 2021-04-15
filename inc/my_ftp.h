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

#include "cmds.h"

#define MAX_LISTEN      5
#define MAX_MSG_LEN     1024
#define BUF_SIZE        1024
#define USAGE           "Usage: myftp <PORT NUMBER>\n"
#define handle_err_int(msg) \
    do { perror(msg); return -1; } while (0)
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
    RPL_NEED_ACCOUNT = 332
} reply_code;

typedef int fd_t;
typedef fd_t sock_t;
typedef struct sockaddr_in addr_t;

typedef struct client {
    fd_t fd;
    addr_t addr;
    enum auth {
        NO_CREDENTIALS,
        USERNAME_ENTERED,
        LOGGED_IN
    } auth;
    struct client *next;
} client_t;

client_t *client_create(void);
void client_destroy(client_t *client);

typedef struct server {
    fd_t fd;
    addr_t addr;
    client_t *client;
    fd_set active_fds;
    fd_set read_fds;
    cmd_t **cmds;
} server_t;

server_t *server_create(in_port_t port);
int server_run(server_t *server);
void server_destroy(server_t *server);

/**
 * @brief Accept a client
 *
 * Adds the client to the linked list, and add its file descriptor into
 * the active set
 * @param server The server accepting the client
 * @return 0 if client was accepted, -1 otherwise
 */
int accept_client(server_t *server);

/**
 * @brief Send a Command Reply Sequence to a client
 *
 * Same as send_client(client_fd, "%d %s", code, line);
 *
 * @param client_fd The client to send the message to
 * @param code The 3-digit reply code
 * @param line Line of text explaining the reply
 * @return ssize_t The number of bytes written to the client
 */
ssize_t send_reply(fd_t client_fd, reply_code code, const char *line);

/**
 * @brief Send a message to the client
 *
 * Automatically adds CRLF to the end of the string.
 *
 * @param client_fd The client to send the message to
 * @param fmt Format of the string to send
 * @param ... Format arguments
 * @return ssize_t The number of bytes written to the client
 */
ssize_t send_client(fd_t client_fd, const char *fmt, ...);

/**
 * @brief Handle the inputs received by the server
 *
 * @param server The server receiving the input
 * @return 0 on success, -1 on error
 */
int handle_inputs(server_t *server);
int handle_cmd(server_t *server, fd_t client_fd, char *cmd);


#endif /* !MY_FTP_H_ */
