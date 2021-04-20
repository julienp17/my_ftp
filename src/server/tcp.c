/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** tcp
*/

#include "my_ftp.h"

addr_t create_tcp_addr(const int port)
{
    addr_t addr;

    memset(&addr, 0, sizeof(addr_t));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    return addr;
}

sock_t create_tcp_sock(void)
{
    return socket(AF_INET, SOCK_STREAM, 0);
}

sock_t create_tcp_serv(const int port)
{
    addr_t addr = create_tcp_addr(port);
    sock_t sock = create_tcp_sock();

    if (sock == -1)
        handle_err_int("socket");
    if (bind(sock, (const struct sockaddr *) &addr, sizeof(addr_t)) == -1) {
        close(sock);
        handle_err_int("bind");
    }
    if (listen(sock, MAX_LISTEN) == -1) {
        close(sock);
        handle_err_int("listen");
    }
    return sock;
}