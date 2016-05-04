#include <cstring>
#include <iostream>
#include <X11/Xlib.h>

using namespace std;

/*
 * Clicks at the specified position (in pixels) on the screen. Origin is at the
 * top left corner of the screen.
 *
 * Adapted from:
 * linuxquestions.org/questions/programming-9/simulating-a-mouse-click-594576/
 */
void click(int x, int y) {
    Display* display = XOpenDisplay(NULL);
    if(display == NULL) {
        cerr << "Could not a initialize connection to an X server." << endl;
        exit(EXIT_FAILURE);
    }
    Window root = DefaultRootWindow(display);
    XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
    XEvent event;
    memset(&event, 0x00, sizeof(event));
    event.type = ButtonPress;
    event.xbutton.button = Button1;
    event.xbutton.same_screen = True;
    XQueryPointer(display, RootWindow(display, DefaultScreen(display)),
                  &event.xbutton.root, &event.xbutton.window,
                  &event.xbutton.x_root, &event.xbutton.y_root,
                  &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    event.xbutton.subwindow = event.xbutton.window;
    while(event.xbutton.subwindow) {
        event.xbutton.window = event.xbutton.subwindow;
        XQueryPointer(display, event.xbutton.window, &event.xbutton.root,
                      &event.xbutton.subwindow, &event.xbutton.x_root,
                      &event.xbutton.y_root, &event.xbutton.x,
                      &event.xbutton.y, &event.xbutton.state);
    }
    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) {
        cerr << "Could not simulate mouse press!" << endl;
        exit(EXIT_FAILURE);
    }
    XFlush(display);
    event.type = ButtonRelease;
    event.xbutton.state = 0x100;
    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) {
        cerr << "Could not release mouse!" << endl;
        exit(EXIT_FAILURE);
    }
    XFlush(display);
}