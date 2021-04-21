/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_retr
*/

#include "my_ftp.h"
#include "my.h"
#include "file_reading.h"

static int send_file(server_t *server, char *buf);

reply_code cmd_retr(server_t *server, client_t *client, char *arg)
{
    reply_code code = 0;
    char *filename = my_strdupcat(my_strdupcat(getcwd(NULL, 0), "/"), arg);
    char *buf = get_file_buffer(filename);

    if (buf == NULL) {
        code = RPL_FILE_UNAVAILABLE_NO_ACCESS;
        send_reply(client->sock, code, "File unavailable.");
        return code;
    }
    code = RPL_FILE_READY;
    send_reply(client->sock, code,"File status okay, opening data connection.");
    if (send_file(server, buf) == -1) {
        code = RPL_CANNOT_OPEN_DATA_CONNECTION;
        send_reply(client->sock, code, "Couldn't send file.");
    } else {
        code = RPL_FILE_ACTION_SUCCESSFUL;
        send_reply(client->sock, code, "Transfer complete.");
    }
    return code;
}

static int send_file(server_t *server, char *buf)
{
    sock_t sock = get_data_sock(server);

    if (sock == -1)
        return -1;
    write(sock, buf, strlen(buf));
    close(sock);
    return 0;
}
