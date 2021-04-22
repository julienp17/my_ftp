/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** cmd_help
*/

#include "my_ftp.h"
#include "my.h"

reply_code cmd_help(server_t *server, client_t *client, char *arg)
{
    reply_code code = RPL_HELP_MSG;
    cmd_t *cmd = NULL;

    if (arg == NULL) {
        send_reply(client->sock, code,"The following commands are recognized.");
        // for (size_t i = 0 ; server->cmds[i] ; i++)
        //     send_str(client->sock, "%8s", server->cmds[i]->name);
    } else {
        cmd = get_cmd(server->cmds, my_str_toupper(arg));
        if (cmd == NULL) {
            code = RPL_CMD_NOT_IMPLEMENTED;
            send_reply(client->sock, code, "Unknown command");
        } else {
            send_reply(client->sock, code, "Description of command :");
            // send_str(client->sock, "%8s: %s", cmd->name, cmd->descr);
        }
    }
    return code;
}