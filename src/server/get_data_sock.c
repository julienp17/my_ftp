/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** get_data_sock
*/

#include "my_ftp.h"

static sock_t get_pasv_sock(const sock_t data_sock);
static sock_t get_actv_sock(const addr_t *addr);

sock_t get_data_sock(const server_t *server)
{
    sock_t data_sock = -1;

    if (server->mode == PASSIVE)
        data_sock = get_pasv_sock(server->data_sock);
    else if (server->mode == ACTIVE)
        data_sock = get_actv_sock(&(server->port_addr));
    return data_sock;
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