/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** handle_inputs
*/

#include "my_ftp.h"
#include "my.h"

static int handle_input(server_t *server, client_t *client);
static int handle_buffer(server_t *server, client_t *client, char *buf);
static int handle_cmd_line(server_t *server, client_t *client, char *cmd_line);
static bool client_disconnected(const ssize_t read_bytes);

int handle_inputs(server_t *server)
{
    for (client_t *client = server->client ; client ; client = client->next)
        if (FD_ISSET(client->sock, &(server->read_fds)))
            handle_input(server, client);
    return 0;
}

static int handle_input(server_t *server, client_t *client)
{
    ssize_t bytes = 0;
    char buf[BUF_SIZE] = "\0";

    memset(buf, 0, BUF_SIZE);
    bytes = read(client->sock, buf, BUF_SIZE);
    FD_CLR(client->sock, &(server->read_fds));
    if (bytes == -1) {
        handle_err_int("read");
    } else if (client_disconnected(bytes)) {
        remove_client(server, client);
    } else {
        buf[bytes] = 0;
        handle_buffer(server, client, strdup(buf));
    }
    return 0;
}

static int handle_buffer(server_t *server, client_t *client, char *buf)
{
    size_t len = strlen(buf);
    int status = 0;

    buf[len - 1] = 0;
    server_log_client("Received from", client->sock);
    server_log("[%s]\n", buf);
    status = handle_cmd_line(server, client, buf);
    free(buf);
    return status;
}

static int handle_cmd_line(server_t *server, client_t *client, char *cmd_line)
{
    char *name = strtok(cmd_line, " ");
    char *arg = strtok(NULL, " ");
    cmd_t *cmd = NULL;

    if (name == NULL) {
        server_log("Empty input\n");
        send_reply(client->sock, RPL_UNKNOWN_COMMAND, "Unknown command.");
        return 0;
    }
    cmd = get_cmd(server->cmds, my_str_toupper(name));
    if (cmd == NULL) {
        send_reply(client->sock, RPL_UNKNOWN_COMMAND, "Unknown command.");
        return -1;
    }
    return handle_cmd(server, client, cmd, arg);
}

static bool client_disconnected(const ssize_t bytes_read)
{
    return bytes_read == 0;
}