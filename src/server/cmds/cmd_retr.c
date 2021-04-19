/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_retr
*/

#include "my_ftp.h"
#include "my.h"
#include "file_reading.h"

reply_code cmd_retr(server_t *server, client_t *client, char *arg)
{
    reply_code code = 0;
    sock_t sock = -1;
    socklen_t len = sizeof(addr_t);
    char *buf = get_file_buffer(my_strdupcat(server->path, arg));

    if (buf == NULL) {
        code = RPL_FILE_UNAVAILABLE;
        send_reply(client->fd, code, "File unavailable.");
        return code;
    }
    send_reply(client->fd, RPL_FILE_READY, "File status okay.");
    sock = accept(client->data_fd, (struct sockaddr *)
                &(client->data_addr), &len);
    if (sock == -1) {
        code = RPL_CANNOT_OPEN_DATA_CONNECTION;
        send_reply(client->fd, code, "File unavailable.");
        return code;
    }
    write(client->data_fd, buf, strlen(buf));
    close(client->data_fd);
    code = RPL_FILE_ACTION_SUCCESSFUL;
    send_reply(client->fd, code, "Transfer complete.");
    return code;
}