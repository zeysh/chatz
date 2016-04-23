#ifndef _DATABASE_H
#define _DATABASE_H

#include <sqlite3.h>
#include "servers.h"

int init_database (char *path);
int create_tables (void);
int query_servers (struct ircserver *servers);

#endif
