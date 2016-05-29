#ifndef _CHANNELS_H
#define _CHANNELS_H

#include "servers.h"

#define MAXCHANLEN 128

struct ircchannel
{
    int sid;
    char channel[MAXCHANLEN];
    struct ircserver serv;
    struct ircchannel *next;
};

struct ircchannel *_channels;

void destroy_channels (void);
int create_channel (struct ircchannel *newinfo);
int update_channel(int sid, struct ircchannel *newinfo);
int delete_channel (int sid);
void channel_connect_by_name(const char *chan);

#endif
