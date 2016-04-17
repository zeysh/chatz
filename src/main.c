/******************************************************************************
 * FILENAME: main.c
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
#include "../include/networking.h"

int main (int argc, char **argv)
{
    GtkBuilder *builder;
    GtkWidget *window;

    gtk_init (&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "ui/chatz.ui", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(window);
    gtk_main();

    return SUCCESS;
}
