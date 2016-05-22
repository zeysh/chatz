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
    free(_channels);
    _channels = NULL;
}

int create_channel(struct ircchannel *newinfo)
{
    return SUCCESS;
}

int update_channel(int sid, struct ircchannel *newinfo)
{
    return SUCCESS;
}

int delete_channel(int sid)
{
    return SUCCESS;
}
