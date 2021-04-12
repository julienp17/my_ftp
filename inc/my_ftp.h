/*
** EPITECH PROJECT, 2021
** my_ftp [WSL: Ubuntu-20.04]
** File description:
** my_ftp
*/

#ifndef MY_FTP_H_
#define MY_FTP_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define MAX_CLIENTS     1024
#define MAX_MSG_LEN     12
#define handle_error(msg) \
    do { perror(msg); return 1; } while (0)


#endif /* !MY_FTP_H_ */
