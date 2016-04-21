#ifndef _SERVER_H
#define _SERVER_H

#define PARAMLEN 128

struct ircserver
{
    int sid;
    char nick[PARAMLEN];
    char user[PARAMLEN];
    char host[PARAMLEN];
    int port;
    char passwd[PARAMLEN];
    int ssl;
};

int create_server (struct ircserver *newinfo);
int update_server (int sid, struct ircserver *newinfo);
int destroy_server (int sid);

#endif
