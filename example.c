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

        if (evt.type == Expose && evt.xexpose.count == 0)
            libwin_redraw(win);

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
    }

    libwin_destroy_win(win);

    return 0;
}

