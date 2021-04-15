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
#include "client.h"

#define MAX_LISTEN      5
#define MAX_MSG_LEN     1024
#define BUF_SIZE        1024
#define DEFAULT_USER    "Anonymous"
#define USAGE           "Usage: myftp <PORT NUMBER>\n"
#define handle_err_int(msg) \
    do { perror(msg); return -1; } while (0)
#define handle_err_null(msg) \
    do { perror(msg); return NULL; } while (0)

typedef int fd_t;
typedef fd_t sock_t;
typedef struct sockaddr_in addr_t;

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
 * Same as send_str(client_fd, "%d %s", code, line);
 *
 * @param client_fd The file descriptor of the client to send the message to
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
 * @param client_fd The file descriptor of the client to send the message to
 * @param fmt Format of the string to send
 * @param ... Format arguments
 * @return ssize_t The number of bytes written to the client
 */
ssize_t send_str(fd_t client_fd, const char *fmt, ...);

/**
 * @brief Handle the inputs received by the server
 *
 * @param server The server receiving the input
 * @return 0 on success, -1 on error
 */
int handle_inputs(server_t *server);
int handle_cmd(server_t *server, client_t *client, char *cmd);


#endif /* !MY_FTP_H_ */
