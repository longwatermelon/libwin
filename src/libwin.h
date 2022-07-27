#ifndef LIBWIN_H
#define LIBWIN_H

#include <stdbool.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

typedef enum
{
    LIBWIN_NONE = 0,
    LIBWIN_UNRESIZABLE = 1
} WindowFlags;

struct Window
{
    Display *dis;
    int scr;
    Window win;
    GC gc;

    Atom del_msg;
};

struct Window *libwin_create_win(const char *title, int width, int height, WindowFlags flags);
void libwin_destroy_win(struct Window *w);

void libwin_clear(struct Window *w);
void libwin_update(struct Window *w);

void libwin_set_bg(struct Window *w, unsigned long bg);
void libwin_set_fg(struct Window *w, unsigned long fg);

unsigned long libwin_color(int r, int g, int b);

bool libwin_should_close(struct Window *w, XEvent *evt);

#endif

