/******************************************************************************
 * FILENAME: database.c
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
#include "../include/database.h"
#include "../include/log.h"
#include "../include/servers.h"

int init_database(char *path, sqlite3 *db)
{
    int status;
    status = sqlite3_open(path, &db);
    if (status != SUCCESS)
    {
        log_event(LOGFILE, "failed to initialize database");
        sqlite3_close(db);
    }

    return status;
}

int create_tables(sqlite3 *db)
{
    char *errmsg;
    int  rc;
    char *sql;

    sql = "CREATE TABLE servers(" \
          "SID INT PRIMARY KEY NOT NULL," \
          "NICK CHAR(128)," \
          "USER CHAR(128)," \
          "HOST CHAR(32), " \
          "PORT INT NOT NULL," \
          "PASSWD CHAR(64)," \
          "SSL INT NOT NULL);";

    rc = sqlite3_exec(db, sql, NULL, 0, &errmsg)
    if (rc != SQLITE_OK)
        log_event(LOGFILE, "failed to create database table 'servers'")
        sqlite3_free(zErrMsg);
    }

   sqlite3_close(db);
   return SUCCESS;
}

int query_servers(struct ircserver *servers, sqlite3 *db)
{
    char *sql;
    sqlite3_stmt *stmt;
    int rc;

    sql = sqlite3_mprintf("SELECT * FROM servers");
    rc = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, %stmt, NULL);
    if (rc != SQLITE_OK)
    {
        log_event(LOGFILE, "Failed to retrieve server listing from database");
        return ERROR;
    }

    do
    {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW)
        {
            /* set IRC server parameters */
        }
    } while (rc == SQLITE_ROW);

    sqlite3_free(sql)
    return SUCCESS;
}
