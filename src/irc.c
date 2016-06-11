/******************************************************************************
 * FILENAME: irc.c
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
#include "../include/irc.h"

int cmd_user(char *buffer, const char *ident, char *server)
{
    snprintf(buffer, BUFFSIZE, "USER %s %s bla :%s\r\n", ident, server, ident);
    return strlen(buffer);
}

int cmd_nick(char *buffer, const char *nick)
{
    snprintf(buffer, BUFFSIZE, "NICK %s\r\n", nick);
    return strlen(buffer);
}

int cmd_pong(char *buffer, const char *server)
{
    snprintf(buf, BUFFSIZE, "PONG %s", server);
    return strlen(buffer);
}

int cmd_join(char *buffer, const char *channels, const char *keys)
{
    if (strlen(channels) > 0)
        snprintf(buffer, BUFFSIZE, "JOIN %s %s\r\n", channels, keys);
    else
        snprintf(buffer, BUFFSIZE, "JOIN 0\r\n");

    return strlen(buffer);
}

int cmd_quit(char *buffer, const char *message)
{
    snprintf(buffer, BUFFSIZE, "QUIT :%s\r\n", message);
    return strlen(buffer);
}

int cmd_operator(char *buffer, const char *nick, const char *passwd)
{
    snprintf(buffer, BUFFSIZE, "OPER %s %s\r\n", nick, passwd);
    return strlen(buffer);
}

int cmd_privmsg(char *buffer, const char *recip, const char *message)
{
    snprintf(buffer, BUFFSIZE, "PRIVMSG %s :%s\r\n", recip, message);
    return strlen(buffer);
}
