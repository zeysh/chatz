/******************************************************************************
 * FILENAME: channels.c
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
#include "../include/channels.h"

void destroy_channels(void)
{
    struct ircchannel* curr;

    while (_channels)
    {
       curr = _channels;
       _channels = _channels->next;
       free(curr);
    }

    _channels = NULL;
}

void channel_connect_by_name(const char *chan)
{
    struct ircchannel *curr;
    int status;

    curr = _channels;
    while (curr)
    {
        if (strcmp(curr->channel, chan) == 0)
        {
            status = connect_server(&curr->serv);
            if (status == SUCCESS)
                curr->serv.is_connected = 1;
            set_serv_conn_status(&curr->serv, status);
            break;
        }
        curr = curr->next;
    }
}
