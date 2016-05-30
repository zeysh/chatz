/******************************************************************************
 * FILENAME: servers.c
 *
 * Copyright (C) 2016 Brandon K. Miller
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 ******************************************************************************
 */

#include "../include/chatz.h"
#include "../include/servers.h"
#include "../include/networking.h"

void destroy_servers(void)
{
    struct ircserver* curr;

    while (_servers)
    {
       curr = _servers;
       _servers= _servers->next;
       free(curr);
    }

    _servers = NULL;
}

int get_serv_conn_status(int sid)
{
    struct ircserver *curr = _servers;
    while (curr)
    {
        if (curr->sid == sid)
        {
            if (curr->is_connected)
                return 1;
        }
    }

    return 0;
}

void set_serv_conn_status(struct ircserver *serv, int status)
{
    struct ircserver *curr = _servers;

    /* check if server exists */
    while (curr)
    {
        if (curr->sid == serv->sid)
        {
            curr->is_connected = status;
            break;
        }
    }

    /* add server to linked list */
    serv->next = _servers;
    _servers   = serv;
}

int connect_server(struct ircserver *serv)
{
    int status;

    status = setup_sock(serv->host, serv->port, &serv->sin);
    if (status == ERROR)
        return ERROR;

    status = tcp_connect(serv->sock, &serv->sin);
    if (status == ERROR)
        return ERROR;

    return SUCCESS;
}
