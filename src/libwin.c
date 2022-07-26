#include "libwin.h"
#include <stdlib.h>

struct Window *libwin_create_win(const char *title, int width, int height)
{
    struct Window *w = malloc(sizeof(struct Window));
    w->dis = XOpenDisplay(0);
    w->scr = DefaultScreen(w->dis);
    unsigned long black = BlackPixel(w->dis, w->scr);
    unsigned long white = WhitePixel(w->dis, w->scr);

    w->win = XCreateSimpleWindow(w->dis, DefaultRootWindow(w->dis), 0, 0, width, height, 5, white, black);
    XSetStandardProperties(w->dis, w->win, title, "test", None, 0, 0, 0);

    XSelectInput(w->dis, w->win, ExposureMask | ButtonPressMask | KeyPressMask);
    w->gc = XCreateGC(w->dis, w->win, 0, 0);

    XSetBackground(w->dis, w->gc, white);
    XSetBackground(w->dis, w->gc, black);

    XClearWindow(w->dis, w->win);
    XMapRaised(w->dis, w->win);
    XFlush(w->dis);

    return w;
}

void libwin_destroy_win(struct Window *w)
{
    XFreeGC(w->dis, w->gc);
    XDestroyWindow(w->dis, w->win);
    XCloseDisplay(w->dis);
    free(w);
}

void libwin_redraw(struct Window *w)
{
}

