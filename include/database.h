#ifndef _DATABASE_H
#define _DATABASE_H

#include <sqlite3.h>
#include "servers.h"

void init_database (char *path);
int create_tables (void);
int query_servers (void);
int query_users (void);

#endif
