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
#include <fcntl.h>

#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "cmds.h"
#include "client.h"

#define MAX_LISTEN          5
#define MAX_MSG_LEN         1024
#define MIN_PORT            1024
#define MIN_DYNAMIC_PORT    49152
#define MAX_PORT            65535
#define BUF_SIZE            1024
#define DEFAULT_USER        "Anonymous"
#define USAGE           \
"Usage: myftp port path\n" \
"       port  is the port number on which the server socket listens\n" \
"       path  is the path to the home directory for the Anonymous user\n"

#define handle_err_int(msg) \
    do { perror(msg); return -1; } while (0)
#define handle_err_null(msg) \
    do { perror(msg); return NULL; } while (0)

typedef int fd_t;
typedef fd_t sock_t;
typedef struct sockaddr_in addr_t;

typedef struct server {
    sock_t sock;
    sock_t data_sock;
    addr_t port_addr;
    char *root_dir;
    cmd_t **cmds;
    client_t *client;
    fd_set active_fds;
    fd_set read_fds;
    enum transfer_mode {
        NONE,
        PASSIVE,
        ACTIVE
    } mode;
} server_t;

server_t *server_create(const in_port_t port, const char *path);
int server_run(server_t *server);
void server_destroy(server_t *server);

int server_log(const char *fmt, ...);
int server_log_addr(const char *prefix, const addr_t *addr);
int server_log_server(const char *prefix, const sock_t sock);
int server_log_client(const char *prefix, const sock_t sock);

sock_t get_data_sock(const server_t *server);

addr_t create_tcp_addr(const int port);
sock_t create_tcp_sock(void);
sock_t create_tcp_serv(const int port);

/**
 * @brief Accept a client
 *
 * Call the "accept" syscall, and then call the add_client function
 *
 * @param server The server accepting the client
 * @return 0 if client was accepted, -1 otherwise
 */
int accept_client(server_t *server);

/**
 * @brief Adds a client
 *
 * Adds the client into the server's linked list and active fdset
 *
 * @param server The server adding the client
 * @param client The client to add
 */
void add_client(server_t *server, client_t *client);

/**
 * @brief Remove a client
 *
 * Remove the client from the server's linked list and active fdset,
 * log disconnection, and call client_destroy.
 *
 * @param server The server removing the client
 * @param client The client to remove
 */
void remove_client(server_t *server, client_t *client);

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

/**
 * @brief Determines the logic for handling commands
 *
 * @param server The server on which the commands are launched
 * @param client The client that requested the command
 * @param cmd The requested command
 * @param arg The (optionnal) command argument
 * @return reply_code The reply_code of the launched command
 */
reply_code handle_cmd(server_t *server, client_t *client,
                    cmd_t *cmd, char *arg);


#endif /* !MY_FTP_H_ */
