/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_retr
*/

#include "my_ftp.h"
#include "my.h"
#include "file_reading.h"

static int send_file(server_t *server, char *buf);
static sock_t get_pasv_sock(const sock_t data_sock);
static sock_t get_actv_sock(const addr_t *addr);

reply_code cmd_retr(server_t *server, client_t *client, char *arg)
{
    reply_code code = 0;
    char *buf = get_file_buffer(my_strdupcat(server->path, arg));

    if (buf == NULL) {
        code = RPL_FILE_UNAVAILABLE;
        send_reply(client->fd, code, "File unavailable.");
        return code;
    }
    send_reply(client->fd, RPL_FILE_READY, "File status okay.");
    if (send_file(server, buf) < 0) {
        code = RPL_CANNOT_OPEN_DATA_CONNECTION;
        send_reply(client->fd, code, "Couldn't send file.");
    } else {
        code = RPL_FILE_ACTION_SUCCESSFUL;
        send_reply(client->fd, code, "Transfer complete.");
    }
    return code;
}

static int send_file(server_t *server, char *buf)
{
    sock_t sock = -1;

    if (server->mode == PASSIVE)
        sock = get_pasv_sock(server->pasv_fd);
    else if (server->mode == ACTIVE)
        sock = get_actv_sock(&(server->port_addr));
    if (sock == -1)
        return -1;
    write(sock, buf, strlen(buf));
    close(sock);
    return 0;
}

static sock_t get_pasv_sock(const sock_t data_sock)
{
    addr_t addr;
    socklen_t len = sizeof(addr_t);
    sock_t sock = accept(data_sock, (struct sockaddr *) &addr, &len);;

    if (sock == -1) {
        server_log("RETR: couldn't accept data connection.");
        return -1;
    }
    return sock;
}

static sock_t get_actv_sock(const addr_t *addr)
{
    sock_t sock = create_tcp_sock();

    if (sock == -1) {
        server_log("RETR: couldn't create new socket.");
        return -1;
    }
    server_log_addr("Trying to connect to", addr);
    if (connect(sock, (const struct sockaddr *) addr, sizeof(addr_t)) == -1)
        handle_err_int("connect");
    return sock;
}