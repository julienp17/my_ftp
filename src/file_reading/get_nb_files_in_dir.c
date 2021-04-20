/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** get_nb_files_in_dir
*/

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int get_nb_files_in_dir(char const *pathname)
{
    DIR *directory = NULL;
    struct dirent *dir_ent = NULL;
    int nb_files = 0;

    if ((directory = opendir(pathname)) == NULL) {
        perror(pathname);
        return (-1);
    }
    errno = 0;
    while ((dir_ent = readdir(directory)) != NULL)
        if (strcmp(dir_ent->d_name, ".") && strcmp(dir_ent->d_name, ".."))
            nb_files++;
    if (dir_ent == NULL && errno != 0) {
        perror(pathname);
        return (-1);
    }
    if (closedir(directory) != 0) {
        perror(pathname);
        return (-1);
    }
    return (nb_files);
}
