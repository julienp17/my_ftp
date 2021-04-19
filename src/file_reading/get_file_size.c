/*
** EPITECH PROJECT, 2020
** PSU_tetris_2019
** File description:
** get_file_size
*/

#include <sys/stat.h>

unsigned int get_file_size(char const *filepath)
{
    struct stat stats;

    if (stat(filepath, &stats) != 0)
        return (-1);
    return (stats.st_size);
}