/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** test_cmd_user
*/

#include <criterion/criterion.h>
#include "my_ftp.h"

Test(_cmd_user, not_logged_in_no_arg)
{
    client_t *client = client_create();
    reply_code code = 0;

    code = cmd_user(NULL, client, NULL);
    cr_assert_eq(code, RPL_NOT_LOGGED_IN);
    cr_assert_eq(client->auth, NOT_LOGGED_IN);
    cr_assert_null(client->username);
    client_destroy(client);
}

Test(_cmd_user, not_logged_in_default_behavior)
{
    client_t *client = client_create();
    char username[] = "tata";
    reply_code code = 0;

    code = cmd_user(NULL, client, strdup(username));
    cr_assert_eq(code, RPL_USERNAME_OK);
    cr_assert_eq(client->auth, USERNAME_ENTERED);
    cr_assert_not_null(client->username);
    cr_assert_str_eq(client->username, username);
    client_destroy(client);
}

Test(_cmd_user, not_logged_in_called_twice)
{
    client_t *client = client_create();
    char username[] = "tata";
    char snd_username[] = "toto";
    reply_code code = 0;

    code = cmd_user(NULL, client, strdup(username));
    cr_assert_eq(code, RPL_USERNAME_OK);
    cr_assert_eq(client->auth, USERNAME_ENTERED);
    cr_assert_not_null(client->username);
    cr_assert_str_eq(client->username, username);

    code = cmd_user(NULL, client, strdup(snd_username));
    cr_assert_eq(code, RPL_USERNAME_OK);
    cr_assert_eq(client->auth, USERNAME_ENTERED);
    cr_assert_not_null(client->username);
    cr_assert_str_eq(client->username, snd_username);
    client_destroy(client);
}

Test(_cmd_user, already_logged_in_no_arg)
{
    client_t *client = client_create();
    char username[] = "Anonymous";
    reply_code code = 0;

    client->auth = LOGGED_IN;
    client->username = strdup(username);
    code = cmd_user(NULL, client, NULL);
    cr_assert_eq(code, RPL_NOT_LOGGED_IN);
    cr_assert_eq(client->auth, LOGGED_IN);
    cr_assert_not_null(client->username);
    cr_assert_str_eq(client->username, username);
    client_destroy(client);
}

Test(_cmd_user, already_logged_in_with_arg)
{
    client_t *client = client_create();
    char username[] = "Anonymous";
    reply_code code = 0;

    client->auth = LOGGED_IN;
    client->username = strdup(username);
    code = cmd_user(NULL, client, "tata");
    cr_assert_eq(code, RPL_NOT_LOGGED_IN);
    cr_assert_eq(client->auth, LOGGED_IN);
    cr_assert_not_null(client->username);
    client_destroy(client);
}