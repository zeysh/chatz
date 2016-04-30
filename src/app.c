#include "../include/chatz.h"
#include "../include/app.h"

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
}

static void chatz_activate(GApplication *app)
{
}

static void chatz_open(GApplication *app, GFile **files,
                       gint n_files, const gchar *hint)
{
}

static void chatz_class_init(ChatzAppClass *class)
{
    G_APPLICATION_CLASS(class)->activate = chatz_activate;
}

ChatzApp *chatz_new(void)
{
    return g_object_new(CHATZ_APP_TYPE, "application-id", "chatz",
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
