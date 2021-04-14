/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** handle_cmds
*/

#include "my_ftp.h"

int handle_cmd(server_t *server, char *cmd)
{
    (void)server;
    printf("Received: %s\n", cmd);
    return 0;
}