/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_stor
*/

#include "my_ftp.h"
#include "my.h"

static int recv_file(server_t *server, const char *filename);

reply_code cmd_stor(server_t *server, client_t *client, char *arg)
{
    reply_code code = 0;
    char *filename = NULL;

    if (arg == NULL) {
        code = RPL_SYNTAX_ERROR;
        send_reply(client->sock, code, "No file specified for upload.");
        return code;
    }
    filename = my_strdupcat(my_strdupcat(getcwd(NULL, 0), "/"), arg);
    code = RPL_FILE_READY;
    send_reply(client->sock, code, "Opening data connection for file upload.");
    if (recv_file(server, filename) == -1) {
        code = RPL_CANNOT_OPEN_DATA_CONNECTION;
        send_reply(client->sock, code, "Couldn't upload file.");
    } else {
        code = RPL_FILE_ACTION_SUCCESSFUL;
        send_reply(client->sock, code, "Successfully uploaded file.");
    }
    free(filename);
    return code;
}

static int recv_file(server_t *server, const char *filename)
{
    sock_t sock = get_data_sock(server);
    char buf[BUF_SIZE] = "\0";
    fd_t fd = -1;
    ssize_t bytes = 0;

    if (sock == -1)
        return -1;
    fd = open(filename, O_WRONLY | O_CREAT, 0644);
    if (fd == -1)
        handle_err_int("open");
    while ((bytes = read(sock, buf, BUF_SIZE)) > 0) {
        buf[bytes] = 0;
        write(fd, buf, strlen(buf));
    }
    close(sock);
    close(fd);
    return 0;
}