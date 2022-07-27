#include "libwin.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int main()
{
    struct Window *win = libwin_create_win("Window test", 800, 600, LIBWIN_UNRESIZABLE);

    XEvent evt;
    KeySym key;
    char text[255];

    bool running = true;

    while (running)
    {
        XNextEvent(win->dis, &evt);

        if (libwin_should_close(win, &evt))
            running = false;


        /* if (evt.type == Expose && evt.xexpose.count == 0) */

        if (evt.type == KeyPress && XLookupString(&evt.xkey, text, 255, &key, 0) == 1)
        {
            if (text[0] == 'q')
                running = false;

            printf("Pressed %c\n", text[0]);
        }

        if (evt.type == ButtonPress)
        {
            printf("Mouse at %d, %d\n", evt.xbutton.x, evt.xbutton.y);
        }

        libwin_clear(win);

        /* libwin_set_fg(win, WhitePixel(win->dis, win->scr)); */
        libwin_set_fg(win, libwin_color(255, 0, 0));
        libwin_set_bg(win, BlackPixel(win->dis, win->scr));

        XDrawLine(win->dis, win->win, win->gc, 100, 100, 200, 100);
        XDrawString(win->dis, win->win, win->gc, 100, 300, "hello", 5);

        libwin_update(win);
    }

    libwin_destroy_win(win);

    return 0;
}

