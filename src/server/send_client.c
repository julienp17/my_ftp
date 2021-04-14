/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** send_client
*/

#include "my_ftp.h"

ssize_t send_reply(fd_t client_fd, ftp_reply_code code, const char *line)
{
    return send_client(client_fd, "%d %s", code, line);
}

ssize_t send_client(fd_t client_fd, const char *fmt, ...)
{
    char buf[BUF_SIZE] = "\0";
    size_t len = 0;
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, BUF_SIZE - 2, fmt, args);
    va_end(args);
    len = strlen(buf);
    buf[len] = '\r';
    buf[len + 1] = '\n';
    buf[len + 2] = '\0';
    return write(client_fd, buf, strlen(buf));
}