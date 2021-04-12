/*
** EPITECH PROJECT, 2021
** my_ftp [WSL: Ubuntu-20.04]
** File description:
** main
*/

#include "my_ftp.h"

int main(int ac, char **av)
{
    int server_fd = 0;
    int client_fd = 0;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char const msg[] = "Hello world!\n";

    if (ac != 2) {
        fprintf(stderr, "Usage: myftp <PORT NUMBER>\n");
        return 1;
    }
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(atoi(av[1]));
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
        handle_error("socket");
    if (bind(server_fd, (const struct sockaddr *) &server_addr, len) == - 1)
        handle_error("bind");
    if (listen(server_fd, MAX_CLIENTS) == -1)
        handle_error("listen");
    client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &len);
    if (client_fd == -1)
        handle_error("accept");
    printf("Connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    send(client_fd, msg, strlen(msg), 0);
    close(client_fd);
    close(server_fd);
    return 0;
}