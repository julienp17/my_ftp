/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_list
*/

#include "my_ftp.h"
#include "file_reading.h"
#include "my.h"

static int send_file_list(server_t *server, char **filenames);

reply_code cmd_list(server_t *server, client_t *client, char *arg)
{
    reply_code code = 0;
    char **list = get_filenames_in_dir(getcwd(NULL, 0));

    (void)arg;
    if (list == NULL) {
        code = RPL_FILE_UNAVAILABLE_BUSY;
        send_reply(client->sock, code, "Couldn't get directory listing.");
        return code;
    }
    send_reply(client->sock, RPL_FILE_READY, "Sending directory listing.");
    if (send_file_list(server, list) == -1) {
        code = RPL_CANNOT_OPEN_DATA_CONNECTION;
        send_reply(client->sock, code, "Couldn't send directory listing.");
    } else {
        code = RPL_FILE_ACTION_SUCCESSFUL;
        send_reply(client->sock, code, "Directory send OK.");
    }
    return code;
}

static int send_file_list(server_t *server, char **filenames)
{
    sock_t sock = get_data_sock(server);

    if (sock == -1)
        return -1;
    for (size_t i = 0 ; filenames[i] ; i++)
        send_str(sock, "%s", filenames[i]);
    close(sock);
    return 0;
}