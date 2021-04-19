/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_pasv
*/

#include "my_ftp.h"

static sock_t get_free_socket(addr_t *addr);
static char *get_passive_pattern(const addr_t *addr, const in_port_t port);

reply_code cmd_pasv(server_t *server, client_t *client, char *arg)
{
    reply_code code = 0;

    (void)arg;
    client->data_addr = client->addr;
    client->data_fd = get_free_socket(&(client->data_addr));
    if (client->data_fd == -1) {
        code = RPL_SERVICE_NOT_AVAILABLE;
        send_reply(client->fd, code, "Service not available, retry later.");
        server_log("No more ports available.\n");
    } else {
        code = RPL_PASSIVE_MODE;
        send_str(client->fd, "%d %s (%s).", code, "Entering PASSIVE mode",
        get_passive_pattern(&(client->data_addr), client->data_addr.sin_port));
        server->mode = PASSIVE;
    }
    return code;
}

static sock_t get_free_socket(addr_t *addr)
{
    sock_t sock = -1;

    addr->sin_port = MIN_DYNAMIC_PORT - 1;
    while (sock == -1 && addr->sin_port < MAX_PORT) {
        addr->sin_port++;
        sock = create_tcp_sock(*addr);
    }
    return sock;
}

static char *get_passive_pattern(const addr_t *addr, const in_port_t port)
{
    char buf[BUF_SIZE] = "\0";
    const uint32_t ip = addr->sin_addr.s_addr;
    const in_port_t port = addr->sin_port;

    snprintf(buf, BUF_SIZE, "%u,%u,%u,%u,%u,%u",
        ip & 0xff, (ip >> 8) & 0xff, (ip >> 16) & 0xff, (ip >> 24) & 0xff,
        port / 256, port % 256);
    return strdup(buf);
}