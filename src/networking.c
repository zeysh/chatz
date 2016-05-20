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

/* TODO -- Something, somewhere needs to call pthread_mutex_init and pthread_mutex_destroy on this thing */
static pthread_mutex_t _sndlock;

int sock_open(const char *host, int port)
{
    int fd;
    char *ip;
    struct hostent *he;
    struct in_addr **addrs;
    struct sockaddr_in server;

    /* Resolve DNS if host is not an IP address */
    if ((he = gethostbyname(host)) == NULL)
        return -1;

    addrs = (struct in_addr **)he->h_addr_list;
    ip = inet_ntoa(*addrs[0]);

    /* Establish connection */
    fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd == -1)
        return -1;

    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (connect(fd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        close(fd);
        return -1;
    }

    return fd;
}

void sock_close(int fd)
{
    close(fd);
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
