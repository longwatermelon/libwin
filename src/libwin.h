#ifndef LIBWIN_H
#define LIBWIN_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

struct Window
{
    Display *dis;
    int scr;
    Window win;
    GC gc;
};

struct Window *libwin_create_win(const char *title, int width, int height);
void libwin_destroy_win(struct Window *w);

void libwin_redraw(struct Window *w);

#endif

