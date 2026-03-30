#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <iostream>
#include <string>

class Rect
{
public:
    Rect(int x,int y,int w,int h) : mx(x),my(y),mw(w),mh(h){}
    
    void Draw(Display* dpy,Window* w, GC* gc)
    {
       
        XFillRectangle(dpy,*w,*gc,mx,my,mw,mh);
    }
    
        
    
    int mx;
    int my;
    int mh;
    int mw;
};





int main(int argc,char** argv)
{
    Rect* r = new Rect(150,150,150,150); 
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
            
            KeySym keysym = XLookupKeysym(&ev.xkey,0);         
                        
            if(keysym == XK_Up ){
                r->my = r->my - 2;
            }
            
            if(keysym == XK_Down ){
                r->my = r->my + 2;
            }

            if(keysym == XK_Left ){
                r->mx = r->mx - 2;
            }
            if(keysym == XK_Right ){
                r->mx = r->mx + 2;
            }

        }
        


        
         XClearWindow(dpy,w);

         r->Draw(dpy,&w,&gc);

         XFlush(dpy);        
        
                




        // nanosleep(&req,&rem);
        // if(rem.tv_nsec < 1000)
        //     nanosleep(&rem,NULL);



    }
exit:
    XCloseDisplay(dpy);
    return 0;

}
