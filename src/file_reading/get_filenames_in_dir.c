/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** get_filenames_in_dir
*/

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "file_reading.h"

static int fill_filenames(const char *pathname, char **filenames);

char **get_filenames_in_dir(const char *pathname)
{
    char **filenames = NULL;
    int nb_files = get_nb_files_in_dir(pathname);

    if (nb_files < 0)
        return NULL;
    filenames = malloc(sizeof(char *) * (nb_files + 1));
    if (filenames == NULL) {
        perror("malloc");
        return NULL;
    }
    filenames[nb_files] = NULL;
    if (fill_filenames(pathname, filenames) == -1)
        return NULL;
    return filenames;
}

static int fill_filenames(const char *pathname, char **filenames)
{
    struct dirent *dir_ent = NULL;
    DIR *dir = opendir(pathname);
    int i = 0;

    if (dir == NULL) {
        perror(pathname);
        return -1;
    }
    while ((dir_ent = readdir(dir)) != NULL)
        if (strcmp(dir_ent->d_name, ".") && strcmp(dir_ent->d_name, ".."))
            filenames[i++] = strdup(dir_ent->d_name);
    closedir(dir);
    return 0;
}