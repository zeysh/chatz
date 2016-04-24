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
};

void destroy_servers (void);
int create_server (struct ircserver *newinfo);
int update_server (int sid, struct ircserver *newinfo);
int delete_server (int sid);

int _nservs;
struct ircserver *_servers;

#endif
