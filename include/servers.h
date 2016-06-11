#ifndef _SERVER_H
#define _SERVER_H

#include "networking.h"
#define PARAMLEN 128

struct ircserver
{
    int sid;
    char host[PARAMLEN];
    int port;
    char passwd[PARAMLEN];
    int ssl;
    int is_connected;
    struct ircserver *next;
    int sock;
    struct sockaddr_in sin;
    char *rbuf;
};

struct ircserver *_servers;

void destroy_servers (void);
int connect_server (struct ircserver *serv);
int get_serv_conn_status (int sid);
void set_serv_conn_status(struct ircserver *serv, int status);

#endif
