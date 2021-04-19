/*
** EPITECH PROJECT, 2019
** my_sokoban
** File description:
** Get the file buffer
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "file_reading.h"

char *get_file_buffer(char const *filepath)
{
    int fd = 0;
    unsigned int file_size = get_file_size(filepath);
    char *buffer = NULL;

    if (filepath == NULL)
        return NULL;
    file_size = get_file_size(filepath);
    buffer = malloc(sizeof(char) * (file_size + 1));
    if ((fd = open(filepath, O_RDONLY)) == -1) {
        perror(filepath);
        return (NULL);
    }
    if (read(fd, buffer, file_size) == -1) {
        perror(filepath);
        return (NULL);
    }
    buffer[file_size] = '\0';
    close(fd);
    return (buffer);
}