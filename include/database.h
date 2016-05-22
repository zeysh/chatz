#ifndef _DATABASE_H
#define _DATABASE_H

#define MAXSQLLEN 512

#include <sqlite3.h>
#include "servers.h"

void init_database (char *path);
int create_tables (void);
int query_server_by_sid (int sid, struct ircserver *serv);
int query_users (void);
int query_channels (void);

#endif
