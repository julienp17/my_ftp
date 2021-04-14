/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** socket
*/

#include "my_ftp.h"

sock_t *socket_create(void)
{
    sock_t *sock = malloc(sizeof(sock_t));

    if (sock == NULL)
        handle_err_null("malloc");
    sock->fd = -1;
    sock->len = sizeof(struct sockaddr_in);
    memset(&(sock->addr), 0, sock->len);
    return sock;
}