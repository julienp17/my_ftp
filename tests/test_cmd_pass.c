/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** test_cmd_pass
*/

#include <criterion/criterion.h>
#include "my_ftp.h"

Test(_cmd_pass, not_logged_in_no_arg)
{
    client_t *client = client_create();
    reply_code code = 0;

    code = cmd_pass(NULL, client, NULL);
    cr_assert_eq(code, RPL_BAD_SEQUENCE);
    cr_assert_eq(client->auth, NOT_LOGGED_IN);
    cr_assert_null(client->username);
    client_destroy(client);
}

Test(_cmd_pass, not_logged_in_with_arg)
{
    client_t *client = client_create();
    char password[] = "word";
    reply_code code = 0;

    code = cmd_pass(NULL, client, password);
    cr_assert_eq(code, RPL_BAD_SEQUENCE);
    cr_assert_eq(client->auth, NOT_LOGGED_IN);
    cr_assert_null(client->username);
    client_destroy(client);
}

Test(_cmd_pass, username_is_anonymous_no_arg)
{
    client_t *client = client_create();
    const char username[] = "Anonymous";
    reply_code code = 0;

    client->auth = USERNAME_ENTERED;
    client->username = strdup(username);
    code = cmd_pass(NULL, client, NULL);
    cr_assert_eq(code, RPL_LOGGED_IN);
    cr_assert_eq(client->auth, LOGGED_IN);
    cr_assert_not_null(client->username);
    cr_assert_str_eq(client->username, username);
    client_destroy(client);
}

Test(_cmd_pass, username_is_anonymous_with_arg)
{
    client_t *client = client_create();
    const char username[] = "Anonymous";
    char password[] = "word";
    reply_code code = 0;

    client->auth = USERNAME_ENTERED;
    client->username = strdup(username);
    code = cmd_pass(NULL, client, password);
    cr_assert_eq(code, RPL_LOGGED_IN);
    cr_assert_eq(client->auth, LOGGED_IN);
    cr_assert_not_null(client->username);
    cr_assert_str_eq(client->username, username);
    client_destroy(client);
}

Test(_cmd_pass, username_is_not_anonymous_no_arg)
{
    client_t *client = client_create();
    const char username[] = "toto";
    reply_code code = 0;

    client->auth = USERNAME_ENTERED;
    client->username = strdup(username);
    code = cmd_pass(NULL, client, NULL);
    cr_assert_eq(code, RPL_NOT_LOGGED_IN);
    cr_assert_eq(client->auth, NOT_LOGGED_IN);
    cr_assert_null(client->username);
    client_destroy(client);
}

Test(_cmd_pass, username_is_not_anonymous_with_arg)
{
    client_t *client = client_create();
    const char username[] = "toto";
    char password[] = "word";
    reply_code code = 0;

    client->auth = USERNAME_ENTERED;
    client->username = strdup(username);
    code = cmd_pass(NULL, client, password);
    cr_assert_eq(code, RPL_NOT_LOGGED_IN);
    cr_assert_eq(client->auth, NOT_LOGGED_IN);
    cr_assert_null(client->username);
    client_destroy(client);
}

Test(_cmd_pass, already_logged_in_no_arg)
{
    client_t *client = client_create();
    const char username[] = "Anonymous";
    reply_code code = 0;

    client->auth = LOGGED_IN;
    client->username = strdup(username);
    code = cmd_pass(NULL, client, NULL);
    cr_assert_eq(code, RPL_LOGGED_IN);
    cr_assert_eq(client->auth, LOGGED_IN);
    cr_assert_not_null(client->username);
    cr_assert_str_eq(client->username, username);
    client_destroy(client);
}

Test(_cmd_pass, already_logged_in_with_arg)
{
    client_t *client = client_create();
    const char username[] = "Anonymous";
    char password[] = "hey";
    reply_code code = 0;

    client->auth = LOGGED_IN;
    client->username = strdup(username);
    code = cmd_pass(NULL, client, password);
    cr_assert_eq(code, RPL_LOGGED_IN);
    cr_assert_eq(client->auth, LOGGED_IN);
    cr_assert_not_null(client->username);
    cr_assert_str_eq(client->username, username);
    client_destroy(client);
}