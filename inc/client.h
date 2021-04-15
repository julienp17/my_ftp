/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** client
*/

#ifndef CLIENT_H_
#define CLIENT_H_

#include <netinet/in.h>
#include <arpa/inet.h>

typedef int fd_t;
typedef struct sockaddr_in addr_t;

typedef struct client {
    fd_t fd;
    addr_t addr;
    char *username;
    enum auth {
        NOT_LOGGED_IN,
        USERNAME_ENTERED,
        LOGGED_IN
    } auth;
    struct client *next;
} client_t;

client_t *client_create(void);
void client_destroy(client_t *client);


#endif /* !CLIENT_H_ */
