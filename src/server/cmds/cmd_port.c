/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_port
*/

#include "my_ftp.h"
#include "my.h"

static int parse_ip(char *arg, uint32_t *ip);
static int parse_port(char *arg, in_port_t *port);

reply_code cmd_port(server_t *server, client_t *client, char *arg)
{
    reply_code code = 0;
    uint32_t ip = 0;
    in_port_t port = 0;

    if (!arg || parse_ip(strdup(arg), &ip) < 0 || parse_port(arg, &port) < 0) {
        code = RPL_SYNTAX_ERROR;
        send_reply(client->fd, code, "Parameter error.");
    } else {
        code = RPL_CMD_OK;
        send_reply(client->fd, code, "Entering ACTIVE mode.");
        server->mode = ACTIVE;
    }
    return code;
}

static int parse_ip(char *arg, uint32_t *ip)
{
    char *token = strtok(arg, ",");
    int ip_nb = 0;

    for (int i = 0 ; i < 4 ; i++) {
        if (token == NULL || !my_str_isnum_pos(token))
            return -1;
        ip_nb = atoi(token);
        if (ip_nb < 0 || ip_nb > 255)
            return -1;
        *ip = (*ip << 8) + ip_nb;
        token = strtok(NULL, ",");
    }
    *ip = ntohl(*ip);
    return 0;
}

static int parse_port(char *arg, in_port_t *port)
{
    char *token = strtok(arg, ",");
    int port_nb = 0;

    for (int i = 0 ; i < 3 ; i++)
        if (strtok(NULL, ",") == NULL)
            return -1;
    token = strtok(NULL, ",");
    if (token == NULL || !my_str_isnum_pos(token))
        return -1;
    port_nb = atoi(token);
    if (port_nb < 0 || port_nb > 255)
        return -1;
    *port = port_nb * 256;
    token = strtok(NULL, ",");
    if (token == NULL || !my_str_isnum_pos(token))
        return -1;
    port_nb = atoi(token);
    if (port_nb < 0 || port_nb > 255)
        return -1;
    *port = *port + port_nb;
    return 0;
}