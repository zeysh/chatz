#ifndef _DATABASE_H
#define _DATABASE_H

#include <sqlite3.h>

int init_database (char *path, sqlite3 *db);
int query_servers (struct ircserver *servers, sqlite3 *db);

#endif
