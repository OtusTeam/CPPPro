#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <iostream>
#include <string>

void PrintHelloWorld(Display* dpy,Window& w, GC& gc)
{
        std::string s = "Hello World!";
        XWindowAttributes xwattr;
        XGetWindowAttributes(dpy,w,&xwattr);
        
        int x_center = (xwattr.width / 2);
        int y_height = (xwattr.height / 2);

        XDrawString(dpy,w,gc,x_center,y_height,s.c_str(),s.size());
        
        
}


int main(int argc,char** argv)
{
    Display * dpy = 0;
    Window w;
    XEvent ev;
    GC gc;
    int s;

    if(!(dpy = XOpenDisplay(0x0))) {
        std::cout << "DISPLAY FAILED TO OPEN!" << std::endl;
        return -1;
    }

    s = DefaultScreen(dpy);

    w = XCreateSimpleWindow(dpy,RootWindow(dpy,s),300,300,500,350,1,
                            BlackPixel(dpy,s),WhitePixel(dpy,s));

    XSelectInput(dpy, w, ExposureMask | KeyPressMask | PointerMotionMask);
    XMapWindow(dpy, w);

    gc = XCreateGC(dpy,w,0,0);

    // struct timespec rem;
    // struct timespec req = {0,160000000};


    for(;;)
    {
        XNextEvent(dpy, &ev);
        //XPeekEvent(dpy,&ev);

        if(ev.type == KeyPress){
            if(ev.xkey.keycode == 9){ /*ESCAPE*/
                goto exit;
            }

        }

        
         XClearWindow(dpy,w);

         PrintHelloWorld(dpy,w,gc);

         XFlush(dpy);        
        
                




        // nanosleep(&req,&rem);
        // if(rem.tv_nsec < 1000)
        //     nanosleep(&rem,NULL);



    }
exit:
    XCloseDisplay(dpy);
    return 0;

}
