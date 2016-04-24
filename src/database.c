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

static sqlite3 *_db;

int init_database(char *path)
{
    int status;

    status = sqlite3_open(path, &_db);
    if (status != SUCCESS)
    {
        log_event(LOGFILE, "failed to initialize database");
        sqlite3_close(_db);
    }

    return status;
}

static int insert_chatz_serv(void)
{
    char *errmsg, *sql;
    int rc;

    sql = "INSERT INTO servers (host, port, ssl) " \
          "VALUES ('74.140.209.140', 6697, 0);";

    rc = sqlite3_exec(_db, sql, NULL, 0, &errmsg);
    if (rc != SQLITE_OK)
    {
        log_event(LOGFILE, "Failed to insert chatz server info");
        log_event(LOGFILE, errmsg);
        return ERROR;
    }

    return SUCCESS;
}

static int insert_chatz_chan(void)
{
    char *errmsg, *sql;
    int rc;

    sql = "INSERT INTO channels (sid, channel) " \
          "VALUES (1, '#chatz');";

    rc = sqlite3_exec(_db, sql, NULL, 0, &errmsg);
    if (rc != SQLITE_OK)
    {
        log_event(LOGFILE, "Failed to insert chatz channel info into database");
        log_event(LOGFILE, errmsg);
        return ERROR;
    }

    return SUCCESS;
}

static int insert_chatz_user(void)
{
    char *errmsg, *sql;
    int rc;

    sql = "INSERT INTO users (sid, user, nick) " \
          "VALUES (1, 'chatzirc', 'chatzuser');";

    rc = sqlite3_exec(_db, sql, NULL, 0, &errmsg);
    if (rc != SQLITE_OK)
    {
        log_event(LOGFILE, "Failed to insert chatz user info into database");
        log_event(LOGFILE, errmsg);
        return ERROR;
    }

    return SUCCESS;
}

int create_tables(void)
{
    char *errmsg, *sql;
    int  rc;

    sql = "CREATE TABLE servers(" \
          "id INTEGER PRIMARY KEY AUTOINCREMENT," \
          "host CHAR(32), " \
          "port INT NOT NULL," \
          "passwd CHAR(64)," \
          "ssl INT NOT NULL);";

    rc = sqlite3_exec(_db, sql, NULL, 0, &errmsg);
    if (rc != SQLITE_OK)
    {
        log_event(LOGFILE, "Failed to create database table 'servers'");
        log_event(LOGFILE, errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(_db);
        return ERROR;
    }

    insert_chatz_serv();

    sql = "CREATE TABLE channels(" \
          "id INTEGER PRIMARY KEY AUTOINCREMENT," \
          "sid INT NOT NULL," \
          "channel CHAR(64));";

    rc = sqlite3_exec(_db, sql, NULL, 0, &errmsg);
    if (rc != SQLITE_OK)
    {
        log_event(LOGFILE, "Failed to create database table 'channels'");
        log_event(LOGFILE, errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(_db);
        return ERROR;
    }

    insert_chatz_chan();

    sql = "CREATE TABLE users(" \
          "id INTEGER PRIMARY KEY AUTOINCREMENT," \
          "sid INT NOT NULL," \
          "user CHAR(64) NOT NULL, " \
          "nick CHAR(64) NOT NULL);";

    rc = sqlite3_exec(_db, sql, NULL, 0, &errmsg);
    if (rc != SQLITE_OK)
    {
        log_event(LOGFILE, "Failed to create database table 'users'");
        log_event(LOGFILE, errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(_db);
        return ERROR;
    }

    insert_chatz_user();

    sqlite3_close(_db);
    return SUCCESS;
}

int query_servers(void)
{
    char *sql;
    sqlite3_stmt *stmt;
    int rc, rows = -1;

    sql = sqlite3_mprintf("SELECT * FROM servers");
    rc = sqlite3_prepare_v2(_db, sql, strlen(sql) + 1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        log_event(LOGFILE, "Failed to retrieve server listing from database");
        return ERROR;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ERROR)
    {
        log_event(LOGFILE, "Error retrieving servers from database");
        return ERROR;
    }

    rows = sqlite3_column_int(stmt, 0);
    _servers = (struct ircserver *)malloc(sizeof(struct ircserver) * rows);

    do
    {
        if (rc == SQLITE_ROW)
        {
            /*  set IRC params */
            printf("%s\n", (const char *)sqlite3_column_text(stmt, 1));
        }

        rc = sqlite3_step(stmt);
    } while (rc == SQLITE_ROW);

    sqlite3_free(sql);
    return SUCCESS;
}
