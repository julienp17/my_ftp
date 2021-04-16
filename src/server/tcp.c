/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** tcp
*/

#include "my_ftp.h"

addr_t create_tcp_addr(const in_port_t port)
{
    addr_t addr;
    size_t len = sizeof(addr_t);

    memset(&addr, 0, len);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    return addr;
}

sock_t create_tcp_sock(const addr_t addr)
{
    size_t len = sizeof(addr_t);
    sock_t sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1)
        handle_err_int("socket");
    if (bind(sock, (const struct sockaddr *) &addr, len) == -1)
        handle_err_int("bind");
    if (listen(sock, MAX_LISTEN) == -1)
        handle_err_int("listen");
    return sock;
}