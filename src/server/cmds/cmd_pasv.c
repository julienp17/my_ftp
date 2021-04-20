/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_pasv
*/

#include "my_ftp.h"

static sock_t get_free_socket(in_port_t *port);
static char *get_passive_pattern(const sock_t sock);

reply_code cmd_pasv(server_t *server, client_t *client, char *arg)
{
    reply_code code = 0;
    in_port_t port = 0;

    (void)arg;
    if (server->data_sock != -1)
        close(server->data_sock);
    server->data_sock = get_free_socket(&port);
    if (server->data_sock == -1) {
        code = RPL_SERVICE_NOT_AVAILABLE;
        send_reply(client->sock, code, "Service not available, retry later.");
        server_log("No more ports available.\n");
    } else {
        code = RPL_PASSIVE_MODE;
        send_str(client->sock, "%d %s (%s).", code, "Entering PASSIVE mode",
            get_passive_pattern(server->data_sock));
        server->mode = PASSIVE;
    }
    return code;
}

static sock_t get_free_socket(in_port_t *port)
{
    sock_t sock = -1;

    *port = MIN_DYNAMIC_PORT - 1;
    while (sock == -1 && *port < MAX_PORT) {
        *port = *port + 1;
        sock = create_tcp_serv(*port);
    }
    return sock;
}

static char *get_passive_pattern(const sock_t sock)
{
    char buf[BUF_SIZE] = "\0";
    addr_t addr;
    socklen_t len = sizeof(addr);
    uint32_t ip = 0;
    in_port_t port = 0;

    if (getsockname(sock, (struct sockaddr *) &addr, &len) == -1)
        handle_err_null("getsockname");
    ip = addr.sin_addr.s_addr;
    port = htons(addr.sin_port);
    snprintf(buf, BUF_SIZE, "%u,%u,%u,%u,%u,%u",
        ip & 0xff, (ip >> 8) & 0xff, (ip >> 16) & 0xff, (ip >> 24) & 0xff,
        port / 256, port % 256);
    return strdup(buf);
}