#ifndef _APP_H
#define _APP_H

#include <gtk/gtk.h>

#define CHATZ_APP_TYPE (chatz_get_type ())
#define CHATZ_APP(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), CHATZ_APP_TYPE, ChatzApp))
#define CHATZ_WINDOW_TYPE (chatz_window_get_type ())
#define CHATZ_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), CHATZ_WINDOW_TYPE, ChatzWindow))

typedef struct _ChatzApp       ChatzApp;
typedef struct _ChatzAppClass  ChatzAppClass;
typedef struct _ChatzWindow      ChatzWindow;
typedef struct _ChatzWindowClass ChatzWindowClass;

GType chatz_get_type (void);
ChatzApp *chatz_new (void);
GType chatz_window_get_type (void);
ChatzWindow *chatz_window_new (ChatzApp *app);
void chatz_window_open (ChatzWindow *win, GFile *file);

#endif
