/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** file_is_dir
*/

#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>

bool file_is_dir(const char *path)
{
    struct stat file_stat;

    if (stat(path, &file_stat) == -1)
        return false;
    if (!S_ISDIR(file_stat.st_mode))
        return false;
    return true;
}