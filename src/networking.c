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

int setup_sock(const char *host, int port)
{
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock < 0)
        return ERROR;

    _sin.sin_addr.s_addr = inet_addr(host);
    _sin.sin_family      = AF_INET;
    _sin.sin_port        = htons(port);

    return SUCCESS;
}

int tcp_connect(void)
{
    if (connect(_sock, (struct sockaddr *)&_sin, sizeof(_sin)) < 0)
        return ERROR;

    return SUCCESS;
}

int tcp_send(const char *msg, size_t nb)
{
    while (_sndlock == 1)
        sleep(1);

    _sndlock = 1;
    if (send(_sock, msg, nb, 0) < 0)
    {
        _sndlock = 0;
        return ERROR;
    }
    _sndlock = 0;

    return SUCCESS;
}

int tcp_recv(char *buffer)
{
    int nb;

    if ((nb = read(_sock, buffer, BUFLEN - 1)) > 0)
        buffer[nb] = '\0';

    return nb;
}
