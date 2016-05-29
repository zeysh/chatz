#ifndef _SERVER_H
#define _SERVER_H

#define PARAMLEN 128

struct ircserver
{
    int sid;
    char host[PARAMLEN];
    int port;
    char passwd[PARAMLEN];
    int ssl;
    int is_connected;
};

void destroy_servers (void);
int connect_server (struct ircserver *serv);

int _nservs;
struct ircserver *_servers;

#endif
