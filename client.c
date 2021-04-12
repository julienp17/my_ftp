/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** client
*/

#include "my_ftp.h"

int main(int ac, char **av)
{
    int fd = 0;
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char const msg[] = "Hello world!\n";
    char buffer[1024] = "";

    if (ac != 3) {
        fprintf(stderr, "Usage: client <SERVER ADDRESS> <PORT NUMBER>\n");
        return 1;
    }
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(av[1]);
    addr.sin_port = htons(atoi(av[2]));
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
        handle_error("socket");
    if (connect(fd, (const struct sockaddr *) &addr, len) == -1)
        handle_error("accept");
    printf("Connected to %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
    read(fd, buffer, 1024);
    printf("Server said: %s\n", buffer);
    close(fd);
    return 0;
}