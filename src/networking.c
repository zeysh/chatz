/******************************************************************************
 * FILENAME: networking.c
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
#include "../include/networking.h"

static int _sndlock;

int setup_sock(const char *host, int port, struct sockaddr_in *sin)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return sock;

    sin->sin_addr.s_addr = inet_addr(host);
    sin->sin_family      = AF_INET;
    sin->sin_port        = htons(port);

    return sock;
}

int tcp_connect(int sock, struct sockaddr_in *sin)
{
    if (connect(sock, (struct sockaddr *)sin, sizeof(struct sockaddr_in)) < 0)
        return ERROR;

    return SUCCESS;
}

int tcp_send(int sock, const char *msg, size_t nb)
{
    while (_sndlock == 1)
        sleep(1);

    _sndlock = 1;
    if (send(sock, msg, nb, 0) < 0)
    {
        _sndlock = 0;
        return ERROR;
    }
    _sndlock = 0;

    return SUCCESS;
}

int tcp_recv(int sock, char *buffer)
{
    int nb;

    if ((nb = read(sock, buffer, BUFFSIZE - 1)) > 0)
        buffer[nb] = '\0';

    return nb;
}
