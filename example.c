#include "libwin.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int main()
{
    struct Window *win = libwin_create_win("Window test", 800, 600);

    Atom delete_msg = XInternAtom(win->dis, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(win->dis, win->win, &delete_msg, 1);

    XEvent evt;
    KeySym key;
    char text[255];

    bool running = true;

    while (running)
    {
        XNextEvent(win->dis, &evt);

        if (evt.type == ClientMessage)
        {
            if (evt.xclient.data.l[0] == delete_msg)
                running = false;
        }

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

