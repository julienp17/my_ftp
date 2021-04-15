/*
** EPITECH PROJECT, 2021
** my_ftp [WSL: Ubuntu-20.04]
** File description:
** main
*/

#include "my_ftp.h"

int main(int ac, char **av)
{
    server_t *server = NULL;
    in_port_t port = 0;
    int status = 0;

    if (ac == 2 && strcmp(av[1], "-h") == 0) {
        printf(USAGE);
        return EXIT_SUCCESS;
    } else if (ac != 3) {
        printf(USAGE);
        return EXIT_FAILURE;
    }
    port = htons(atoi(av[1]));
    server = server_create(port, av[2]);
    if (server == NULL)
        return EXIT_FAILURE;
    status = server_run(server);
    server_destroy(server);
    return status;
}