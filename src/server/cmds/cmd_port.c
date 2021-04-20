/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_port
*/

#include "my_ftp.h"
#include "my.h"

static int parse_addr(char *arg, addr_t *addr);
static int parse_ip(char *arg, in_addr_t *ip);
static int parse_port(char *arg, in_port_t *port);
static int parse_nb(char *token);

reply_code cmd_port(server_t *server, client_t *client, char *arg)
{
    reply_code code = 0;

    server->port_addr = create_tcp_addr(0);
    if (arg == NULL || parse_addr(arg, &server->port_addr) == -1) {
        code = RPL_SYNTAX_ERROR;
        send_reply(client->sock, code, "Parameter error.");
    } else {
        code = RPL_CMD_OK;
        send_reply(client->sock, code, "Entering ACTIVE mode.");
        server->mode = ACTIVE;
        server_log_addr("Filled port address with", &server->port_addr);
    }
    return code;
}

static int parse_addr(char *arg, addr_t *addr)
{
    if (parse_ip(strdup(arg), &addr->sin_addr.s_addr) == -1)
        return -1;
    else if (parse_port(arg, &addr->sin_port) == -1)
        return -1;
    return 0;
}

static int parse_ip(char *arg, in_addr_t *ip)
{
    int nb = parse_nb(strtok(arg, ","));

    if (nb == -1)
        return -1;
    *ip = 0;
    *ip = (*ip << 8) + nb;
    for (int i = 0 ; i < 3 ; i++) {
        nb = parse_nb(strtok(NULL, ","));
        if (nb == -1)
            return -1;
        *ip = (*ip << 8) + nb;
    }
    *ip = ntohl(*ip);
    return 0;
}

static int parse_port(char *arg, in_port_t *port)
{
    int nb = 0;

    strtok(arg, ",");
    for (int i = 0 ; i < 3 ; i++)
        if (strtok(NULL, ",") == NULL)
            return -1;
    nb = parse_nb(strtok(NULL, ","));
    if (nb == -1)
        return -1;
    *port = nb * 256;
    nb = parse_nb(strtok(NULL, ","));
    if (nb == -1)
        return -1;
    *port = htons(*port + nb);
    return 0;
}

static int parse_nb(char *token)
{
    int nb = -1;

    if (token == NULL || !my_str_isnum_pos(token))
        return -1;
    nb = atoi(token);
    if (nb < 0 || nb > 255)
        return -1;
    return nb;
}