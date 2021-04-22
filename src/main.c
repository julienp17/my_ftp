/*
** EPITECH PROJECT, 2021
** my_ftp [WSL: Ubuntu-20.04]
** File description:
** main
*/

#include "my_ftp.h"
#include "my.h"

int main(int ac, char **av)
{
    server_t *server = NULL;
    in_port_t port = 0;
    int status = 0;

    if (ac == 2 && strcmp(av[1], "-h") == 0) {
        fprintf(stderr, USAGE);
        return EXIT_SUCCESS;
    } else if (ac != 3 || !my_str_isnum_pos(av[1])) {
        fprintf(stderr, USAGE);
        return 84;
    }
    port = atoi(av[1]);
    server = server_create(port, av[2]);
    if (server == NULL)
        return 84;
    status = server_run(server);
    server_destroy(server);
    return status;
}
