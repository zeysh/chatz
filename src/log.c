/******************************************************************************
 * FILENAME: log.c
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

void log_event(const char *filename, const char *message)
{
    FILE *f;
    time_t now;
    struct tm *stm;
    char *buf;

    f = fopen(filename, "a");
    if (!f)
        return;

    now = time(NULL);
    stm = gmtime(&now);
    buf = (char *)calloc(20, sizeof(char));
    strftime(buf, 20, "%Y-%m-%d %H:%M:%S", stm);
    fprintf(f, "%s %s\n", buf, message);
    free(buf);
    fclose(f);
} /* function log_event */
