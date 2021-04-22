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


int accept_client(server_t *server);
void add_client(server_t *server, client_t *client);
void remove_client(server_t *server, client_t *client);

ssize_t send_reply(fd_t client_fd, reply_code code, const char *line);

ssize_t send_str(fd_t client_fd, const char *fmt, ...);

int handle_inputs(server_t *server);

reply_code handle_cmd(server_t *server, client_t *client,
                    cmd_t *cmd, char *arg);


#endif /* !MY_FTP_H_ */
