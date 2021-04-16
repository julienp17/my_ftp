/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_pasv
*/

#include "my_ftp.h"

static char *get_passive_pattern(const addr_t *addr);

reply_code cmd_pasv(server_t *server, client_t *client, char *arg)
{
    reply_code code = 0;
    sock_t sock = -1;
    addr_t addr = create_tcp_addr(MIN_DYNAMIC_PORT);

    while (sock == -1 && addr.sin_port < MAX_PORT) {
        addr.sin_port++;
        sock = create_tcp_sock(addr);
    }
    if (sock == -1) {
        server_log("No more ports available.\n");
        code = RPL_SERVICE_NOT_AVAILABLE;
        send_reply(client->fd, code, "Service not available, retry later.");
    } else {
        code = RPL_PASSIVE_MODE;
        send_str(client->fd, "%d %s (%s).", code, "Entering PASSIVE mode",
                get_passive_pattern(&addr));
    }
    return code;
}

static char *get_passive_pattern(const addr_t *addr)
{
    char buf[BUF_SIZE] = "\0";
    uint32_t ip = addr->sin_addr.s_addr;
    uint32_t port = addr->sin_port;

    snprintf(buf, BUF_SIZE, "%u,%u,%u,%u,%u,%u",
        ip & 0xff, (ip >> 8) & 0xff, (ip >> 16) & 0xff, (ip >> 24) & 0xff,
        (port >> 8), port & 0xff);
    return buf;
}