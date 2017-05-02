/*
*                               Basic X program:
*
*       This is a very simple X program.  It shows the basics needed to get the
*       simplest X program working.   Compile as:
*               cc testRectangles.c -lX11 -o testRectangle
*
*       When run, pops up a window with Hello World written in it.
*       When the mouse is clicked, the word Hi! appears at the spot.
*       If the window is covered, then uncovered ("exposed"), the
*       Hello World is redrawn - but not the various Hi! items.
*       If a key is pressed nothing happens except if it is q in which
*       case the program quits.
*
*/


#include<stdio.h>
#include<stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
//#include <gtk/gtk.h>
#include<sys/utsname.h>
#include <limits.h>

main(argc,argv)
int argc; char **argv;
{
    Display *mydisplay;
    Window mywindow;
    GC mygc;
    XEvent myevent;
    KeySym mykey;
    XSizeHints myhint;

//System information
            struct utsname uname_pointer;
            uname(&uname_pointer);
           // printf("System name - %s \n", uname_pointer.sysname);


//documents
            FILE* fp;
            char* command;
            char* line;
            int i=0,maxDoc=0;
            line = malloc(200 * sizeof(char));
            command = malloc(200 * sizeof(char));
            strcpy(command,"ls Documents");

            fp = popen(command,"r");

           // char *arr[20];
            const char ptr[20][30];

        while(fgets(line,  INT_MAX, fp))

                     {
                        strcpy(ptr[i],line);

                         i++;
                        if(i>20) break;
                     }
        maxDoc=i;
    
    /*for(i=0;i<=maxDoc;i++)
        printf("%s \n", arr[i]);*/

    int myscreen;
    unsigned long myforeground, mybackground;
    //int i;
    char text[10];
    int done;
    char *sysn = uname_pointer.sysname, *noden = uname_pointer.nodename, *release= uname_pointer.release, *version = uname_pointer.version, *machine= uname_pointer.machine  ;
    char *sysHead= "SYSTEM INFORMATION",*sys = "SYSTEM NAME : ", *node= "NODENAME : ", *releas = "RELEASE : ", *ver = "VERSION : ", *mac = "MACHINE : "; 

    mydisplay = XOpenDisplay("");
    myscreen = DefaultScreen(mydisplay);
    mybackground = WhitePixel(mydisplay,myscreen);
    myforeground = BlackPixel(mydisplay,myscreen);


        /* Suggest where to position the window: */
    myhint.x = 0;
    myhint.y = 0;
    myhint.width = 1500;
    myhint.height = 1500;
    myhint.flags = PPosition | PSize;


        /* Create a window - not displayed yet however: */
    mywindow = XCreateSimpleWindow(mydisplay,DefaultRootWindow(mydisplay),


    myhint.x,myhint.y,myhint.width,myhint.height,5,myforeground,mybackground);




//XSetStandardProperties(mydisplay,mywindow,hello,hello,None,argv,argc,&myhint
//);


        /* Create a Graphics Context (GC) for the window: */
    mygc = XCreateGC(mydisplay,mywindow,0,0);
    XSetBackground(mydisplay,mygc,mybackground);
    XSetForeground(mydisplay,mygc,myforeground);
        /* Select input devices to listen to: */
    XSelectInput(mydisplay,mywindow,ButtonPressMask|KeyPressMask|ExposureMask);
        /* Actually display the window: */
    XMapRaised(mydisplay,mywindow);


        /* Main Event Loop: This is the core of any X program: */
    done = 0;
    while (done==0) {
        XNextEvent(mydisplay,&myevent);
        switch(myevent.type) {
        case Expose: /* Repaint window on expose */
            if (myevent.xexpose.count==0)
              //  XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                //        mygc,50,50,hello,strlen(hello));
          
                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,115,sysHead,strlen(sysHead));

                XDrawLine(mydisplay,mywindow,mygc, 28,120, 142,120);


                 XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,150,sys,strlen(sys)); 
                 XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,175,sysn,strlen(sysn));

                  XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,225,node,strlen(node));
                  XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,250,noden,strlen(noden));

                   XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,300,releas,strlen(releas));
                   XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,325,release,strlen(release));

                    XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,375,ver,strlen(ver));
                    XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,400,version,23 );

                     XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,450,mac,strlen(mac));
                     XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,475,machine,strlen(machine));
 //printf("System name - %s \n", uname_pointer.sysname);

                     /************ DOcuments **********/
            int ycor= 150;

    int k;
                    for(k=0;k<maxDoc;k++){
                   
                        XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,350,ycor,ptr[k],strlen(ptr[k])-1);
                        ycor=ycor+30;
                        }                        
                
            break;

        case MappingNotify: /* Process keyboard mapping changes: */
            XRefreshKeyboardMapping(&myevent);
            break;
        case ButtonPress: /* Process mouse click - output Hi! at mouse: */
        
        if (myevent.type==ButtonPress && myevent.xbutton.x >= 900   && myevent.xbutton.x < 925 && myevent.xbutton.y > 37 &&  myevent.xbutton.y < 62) {
        /* tell where the mouse Button was Pressed */
        
        //   printf("You pressed a button at (%i,%i)\n",
        //   myevent.xbutton.x,myevent.xbutton.y);
        //  XDrawImageString(myevent.xbutton.display,myevent.xbutton.window,
        //  mygc,myevent.xbutton.x,myevent.xbutton.y,hi,strlen(hi));
            system("DISPLAY=:0 gnome-session-quit --logout --no-prompt");
            }

         if (myevent.type==ButtonPress && myevent.xbutton.x >= 350   && myevent.xbutton.x < 425 && myevent.xbutton.y > 135 &&  myevent.xbutton.y < 160) {
//check null of ptr
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[0])+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result,"xdg-open Documents/");
    strcat(result,ptr[0]);
    system(result);

         }

         if (myevent.type==ButtonPress && myevent.xbutton.x >= 900   && myevent.xbutton.x < 925 && myevent.xbutton.y > 37 &&  myevent.xbutton.y < 62) {
        /* tell where the mouse Button was Pressed */
        
        //   printf("You pressed a button at (%i,%i)\n",
        //   myevent.xbutton.x,myevent.xbutton.y);
        //  XDrawImageString(myevent.xbutton.display,myevent.xbutton.window,
        //  mygc,myevent.xbutton.x,myevent.xbutton.y,hi,strlen(hi));
            system("DISPLAY=:0 gnome-session-quit --logout --no-prompt");
            }
	     if (myevent.type==ButtonPress && myevent.xbutton.x >= 900   && myevent.xbutton.x < 925 && myevent.xbutton.y > 37 &&  myevent.xbutton.y < 62) {
        
        }

            break;
        case KeyPress: /* Process key press - quit on q: */
            i = XLookupString(&myevent,text,10,&mykey,0);
            if (i==1 && text[0]=='q') done = 1;
            break;
            
        }
XDrawRectangle(mydisplay, mywindow, mygc, 20, 25, 960, 50);
XDrawRectangle(mydisplay, mywindow, mygc, 900, 37, 25, 25);
XDrawRectangle(mydisplay, mywindow, mygc, 940, 37, 25, 25);
XDrawRectangle(mydisplay, mywindow, mygc, 980, 25, 150, 50);
XDrawRectangle(mydisplay, mywindow, mygc, 1130, 25, 150, 50);
XDrawRectangle(mydisplay, mywindow, mygc, 20, 75, 160,750);
XDrawRectangle(mydisplay, mywindow, mygc, 180, 75, 150,750);
XDrawRectangle(mydisplay, mywindow, mygc, 330, 75, 150,750);
XDrawRectangle(mydisplay, mywindow, mygc, 480, 75, 500,750);
XDrawRectangle(mydisplay, mywindow, mygc, 980, 75, 150,750);
XDrawRectangle(mydisplay, mywindow, mygc, 1130, 75, 150,750);

 
    }


    XFreeGC(mydisplay,mygc);
    XDestroyWindow(mydisplay,mywindow);
    XCloseDisplay(mydisplay);
    exit(0);
}

