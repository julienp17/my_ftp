/*
** EPITECH PROJECT, 2020
** PSU_tetris_2019
** File description:
** file_reading
*/

#ifndef FILE_READING_H_
    #define FILE_READING_H_

    #include <stdbool.h>

    bool file_is_dir(const char *path);

    unsigned int get_file_size(char const *filepath);
    char *get_file_buffer(char const *filepath);

    int get_nb_files_in_dir(char const *pathname);
    char **get_filenames_in_dir(const char *pathname);
#endif