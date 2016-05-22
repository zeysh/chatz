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
#include "../include/channels.h"

#define DARKBLUE  0x252839
#define DARKGREY  0x677077
#define LIGHTGREY 0xb5b5b7
#define GOLDENROD 0xf2b632

enum
{
  LIST_ITEM = 0,
  N_COLUMNS
};

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

    fp = fopen(DBFILE, "r");
    if (fp)
    {
        dbexists = 1;
        fclose(fp);
    }

    init_database(DBFILE);
    if (!dbexists)
        create_tables();

    query_channels();
}

void init_list(GtkWidget *list, const char *title)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes(title,
            renderer, "text", LIST_ITEM, NULL);

    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

    gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));
    g_object_unref(store);
}
void push_channel(GtkWidget *list, const gchar *str)
{
    GtkListStore *store;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);
}

static void init_channel_list(GApplication *app, GtkWidget *grid)
{
    GtkWidget *list;
    GtkTreeSelection *selection;
    struct ircchannel *curr;

    list = gtk_tree_view_new();
    gtk_widget_set_vexpand(list, TRUE);
    gtk_grid_attach(GTK_GRID(grid), list, 0, 1, 8, 8);
    init_list(list, "Channels");
    curr = _channels;
    while (curr)
    {
        push_channel(list, curr->channel);
        curr = curr->next;
    }

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
}

static void init_dm_list(GApplication *app, GtkWidget *grid)
{
    GtkWidget *list;

    list = gtk_tree_view_new();
    gtk_widget_set_hexpand(list, TRUE);
    gtk_widget_set_vexpand(list, TRUE);
    gtk_grid_attach(GTK_GRID(grid), list, 0, 9, 8, 5);
    init_list(list, "Direct Messages");
}

static void init_window(ChatzWindow *win)
{
    gtk_container_set_border_width(GTK_CONTAINER(win), 10);
    gtk_window_set_title(GTK_WINDOW(win), "Chatz");
    gtk_window_set_default_size(GTK_WINDOW(win), 800, 600);
    gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
    g_signal_connect(
        GTK_WIDGET(win),
        "destroy",
        G_CALLBACK(gtk_main_quit),
        NULL
    );
}

static void init_grid(GtkWidget *grid, ChatzWindow *win)
{
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_container_add(GTK_CONTAINER(win), grid);
}

static void init_chan_msg_viewer(GtkWidget * grid)
{
    GtkWidget *view;
    view = gtk_text_view_new();
    gtk_widget_set_vexpand(view, TRUE);
    gtk_grid_attach(GTK_GRID(grid), view, 9, 1, 24, 12);
}

static void init_send_btn(GtkWidget *grid)
{
    GtkWidget *btn;
    btn = gtk_button_new_with_label("Send");
    gtk_widget_set_tooltip_text(btn, "Send a message");
    gtk_grid_attach(GTK_GRID(grid), btn, 9, 13, 1, 1);
}

static void init_msg_entry(GtkWidget *grid)
{
    GtkWidget *entry;

    entry = gtk_entry_new();
    gtk_widget_set_hexpand(entry, TRUE);
    gtk_grid_attach(GTK_GRID(grid), entry, 10, 13, 23, 1);
}

static void chatz_activate(GApplication *app)
{
    ChatzWindow *win;
    GtkWidget *grid;
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    win= gtk_window_new(GTK_WINDOW_TOPLEVEL);

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(
        screen,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    gtk_css_provider_load_from_data(
        GTK_CSS_PROVIDER(provider),
        "GtkWindow {\n"
        "   -GtkWidget-focus-line-width: 0;\n"
        "   background-color: #677077;\n"
        "}\n", -1, NULL
    );

    init_window(win);
    grid = gtk_grid_new();
    init_grid(grid, win);
    init_channel_list(app, grid);
    init_dm_list(app, grid);
    init_chan_msg_viewer(grid);
    init_send_btn(grid);
    init_msg_entry(grid);

     g_object_unref (provider);

    gtk_widget_show_all(GTK_WIDGET(win));
    gtk_main();
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
