/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** log
*/

#include <stdio.h>
#include <stdarg.h>
#include "client.h"

int server_log(const char *fmt, ...)
{
    va_list args;
    int bytes = 0;

    va_start(args, fmt);
    bytes = vfprintf(stderr, fmt, args);
    va_end(args);
    return bytes;
}

int log_client(const char *prefix, const client_t *client)
{
    return (
        fprintf(stderr, "%s from %s:%d\n", prefix,
                inet_ntoa(client->addr.sin_addr), ntohs(client->addr.sin_port))
    );
}