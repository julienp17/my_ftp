/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** log
*/

#include <stdio.h>
#include <stdarg.h>
#include "my_ftp.h"

int server_log(const char *fmt, ...)
{
    va_list args;
    int bytes = 0;

    va_start(args, fmt);
    bytes = vfprintf(stderr, fmt, args);
    va_end(args);
    return bytes;
}

int server_log_addr(const char *prefix, const sock_t sock)
{
    addr_t addr;
    socklen_t len = sizeof(addr_t);

    if (getsockname(sock, (struct sockaddr *) &addr, &len) == -1)
        handle_err_int("getsockname");
    return (
        fprintf(stderr, "%s %s:%d\n", prefix,
                inet_ntoa(addr.sin_addr), htons(addr.sin_port))
    );
}