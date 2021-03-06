/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** my_strdupcat
*/

#include <stdlib.h>
#include <string.h>

char *my_strdupcat(char const *s1, char const *s2)
{
    char *str = NULL;
    unsigned int i = 0;

    if (s1 == NULL || s2 == NULL)
        return NULL;
    str = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
    for (i = 0 ; s1[i] ; i++)
        str[i] = s1[i];
    for (unsigned int j = 0 ; s2[j] ; i++, j++)
        str[i] = s2[j];
    str[i] = '\0';
    return (str);
}