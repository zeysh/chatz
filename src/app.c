/******************************************************************************
 * FILENAME: app.c
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
#include "../include/app.h"
#include "../include/database.h"

struct _ChatzApp
{
    GtkApplication parent;
};

struct _ChatzAppClass
{
    GtkApplicationClass parclass;
};

G_DEFINE_TYPE(ChatzApp, chatz, GTK_TYPE_APPLICATION);

static void chatz_init(struct _ChatzApp *app)
{
    int dbexists = 0;
    FILE *fp;

    if (fp = fopen(DBFILE, "r"))
    {
        dbexists = 1;
        fclose(fp);
    }

    init_database(DBFILE);
    if (!dbexists)
        create_tables();

    query_servers();
}

static void chatz_activate(GApplication *app)
{
    ChatzWindow *win;
    GtkWidget *grid;
    GtkWidget *sendbtn;
    GtkWidget *entry;
    GtkWidget *view;

    /* create window */
    win = chatz_window_new(CHATZ_APP(app));
    gtk_container_set_border_width(GTK_CONTAINER(win), 10);
    gtk_window_set_title(GTK_WINDOW(win), "Chatz");
    gtk_window_set_default_size(GTK_WINDOW(win), 800, 600);
    gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);

    /* create grid for sending messages */
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(win), grid);

    /* create send button */
    sendbtn = gtk_button_new_with_label("Send");
    gtk_widget_set_tooltip_text(sendbtn, "Send a message");
    gtk_grid_attach(GTK_GRID(grid), sendbtn, 9, 0, 1, 1);

    /* create message/entry box */
    entry = gtk_entry_new();
    gtk_widget_set_hexpand(entry, TRUE);
    /* HORIZ SLOT, VERT SLOT, HORIZ CELL,  VERT CELL */
    gtk_grid_attach(GTK_GRID(grid), entry, 10, 0, 23, 1);

    /* create channel viewer */
    view = gtk_tree_view_new();
    gtk_widget_set_hexpand(view, TRUE);
    gtk_widget_set_vexpand(view, TRUE);
    gtk_grid_attach(GTK_GRID(grid), view, 0, 2, 8, 16);

    /* create message viewer */
    view = gtk_text_view_new();
    gtk_widget_set_hexpand(view, TRUE);
    gtk_widget_set_vexpand(view, TRUE);
    gtk_grid_attach(GTK_GRID(grid), view, 9, 2, 24, 16);
    gtk_widget_show_all(GTK_WIDGET(win));
}

static void chatz_open(GApplication *app, GFile **files,
                       gint n_files, const gchar *hint)
{
    GList *windows;
    ChatzWindow *win;
    int i;

    windows = gtk_application_get_windows (GTK_APPLICATION (app));
    if (windows)
        win = CHATZ_WINDOW(windows->data);
    else
        win = chatz_window_new(CHATZ_APP(app));

    /* open tabs for channels */

    gtk_window_present(GTK_WINDOW(win));
}

static void chatz_class_init(ChatzAppClass *class)
{
    G_APPLICATION_CLASS(class)->activate = chatz_activate;
    G_APPLICATION_CLASS(class)->open     = chatz_open;
}

ChatzApp *chatz_new(void)
{
    return g_object_new(CHATZ_APP_TYPE, "application-id", "chatz.irc",
                        "flags", G_APPLICATION_HANDLES_OPEN, NULL);
}

struct _ChatzWindow
{
    GtkApplicationWindow parent;
};

struct _ChatzWindowClass
{
    GtkApplicationWindowClass parent_class;
};

G_DEFINE_TYPE(ChatzWindow, chatz_window, GTK_TYPE_APPLICATION_WINDOW);

static void chatz_window_init (ChatzWindow *win)
{
}

static void chatz_window_class_init (ChatzWindowClass *class)
{
}

ChatzWindow *chatz_window_new (ChatzApp *app)
{
    return g_object_new(CHATZ_WINDOW_TYPE, "application", app, NULL);
}

void chatz_window_open (ChatzWindow *win, GFile *file)
{
}
