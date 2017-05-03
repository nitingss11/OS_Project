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
#include<time.h>

//#define NULL 0
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
                        //printf("%s",ptr[i]); 
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
    char *docHead= "DOCUMENTS";
    char *appHead= "APPLICATIONS",*firefox = "FIREFOX", *cheese = "CHEESE", *writer = "LibreOffice Writer", *sysMonitor = "SYSTEM MONITOR", *calc = "LibreOffice Calc",*impress = "LibreOffice Impress",*UbuSoft= "UBUNTU SOFTWARE";
    char *diskHead = "DISK INFORMATION";
    char *computer = "COMPUTER";

    mydisplay = XOpenDisplay("");
    myscreen = DefaultScreen(mydisplay);
    mybackground = WhitePixel(mydisplay,myscreen);
    myforeground = BlackPixel(mydisplay,myscreen);


        /* Suggest where to position the window: */
    myhint.x = 0;
    myhint.y = 0;
    myhint.width = 1500;
    myhint.height = 750;
    myhint.flags = PPosition | PSize;

    //time



    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    strftime(s, sizeof(s), "%c", tm);
 //   printf("%s\n", s);

    char *dayDT= s;

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
                        mygc,683,55,computer,strlen(computer));  //650, 32, 120, 35

                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,60,dayDT,strlen(dayDT));

                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,115,sysHead,strlen(sysHead));               

                XDrawLine(mydisplay,mywindow,mygc, 28,120, 142,120);

                 
                 XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,370,115,docHead,strlen(docHead));
                 XDrawLine(mydisplay,mywindow,mygc, 365,120, 430,120); 

                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,220,115,appHead,strlen(appHead));
                 XDrawLine(mydisplay,mywindow,mygc, 215,120, 295,120);


                 XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,370,diskHead,strlen(diskHead));
                 XDrawLine(mydisplay,mywindow,mygc, 28,375, 130,375); 

                 
                 XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,150,sys,strlen(sys)); 
                 XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,165,sysn,strlen(sysn));

                  XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,190,node,strlen(node));
                  XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,205,noden,strlen(noden));

                   XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,230,releas,strlen(releas));
                   XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,245,release,strlen(release));

                    XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,270,ver,strlen(ver));
                    XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,285,version,23 );

                     XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,310,mac,strlen(mac));
                     XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,30,325,machine,strlen(machine));


                     //apps-

                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,190,150,firefox,strlen(firefox));

                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,190,180,cheese,strlen(cheese));

                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,190,210,sysMonitor,strlen(sysMonitor));

                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,190,240,writer,strlen(writer));

                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,190,270,calc,strlen(calc));

                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,190,300,impress,strlen(impress));

                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,190,330,UbuSoft,strlen(UbuSoft));

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
      //  printf("You pressed a button at (%i,%i)\n",  myevent.xbutton.x,myevent.xbutton.y);
     //  


        if (myevent.type==ButtonPress && myevent.xbutton.x >= 900   && myevent.xbutton.x < 925 && myevent.xbutton.y > 37 &&  myevent.xbutton.y < 62) {
        /* tell where the mouse Button was Pressed */
        
        //   printf("You pressed a button at (%i,%i)\n",
        //   myevent.xbutton.x,myevent.xbutton.y);
        //  XDrawImageString(myevent.xbutton.display,myevent.xbutton.window,
        //  mygc,myevent.xbutton.x,myevent.xbutton.y,hi,strlen(hi));
            system("DISPLAY=:0 gnome-session-quit --logout --no-prompt");
            }
//doc1 
         if (maxDoc>=1 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 140 &&  myevent.xbutton.y < 155) {
           //check null of ptr
          
          char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[0])+1);//+1 for the zero-terminator
                  //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[0]);
           system(result);
           /// printf("You pressed a button at (%i,%i)\n",myevent.xbutton.x,myevent.xbutton.y);      
             

         }
//doc2
         if (maxDoc>=2 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 170 &&  myevent.xbutton.y < 185) {
            //check null of ptr
           
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[1])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[1]);
           system(result);
              }

//doc3
         if ( maxDoc>=3 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 200 &&  myevent.xbutton.y < 215) {
            //check null of ptr
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[2])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[2]);
           system(result);
              }

//doc4
         if (maxDoc>=4 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 230 &&  myevent.xbutton.y < 245) {
            //check null of ptr
             
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[3])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[3]);
           system(result);
              }
//doc5
         if (maxDoc>=4 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 260 &&  myevent.xbutton.y < 275) {
            //check null of ptr
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[4])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[4]);
           system(result);
              }

//doc6
         if (maxDoc>=5 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 290 &&  myevent.xbutton.y < 305) {
            //check null of ptr
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[5])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[5]);
           system(result);
              }

//doc7
         if (maxDoc>=6 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 320 &&  myevent.xbutton.y < 335) {
            //check null of ptr
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[6])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[6]);
           system(result);
              }  

//doc8
         if (maxDoc>=7 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 350 &&  myevent.xbutton.y < 365) {
            //check null of ptr
             
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[7])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[7]);
           system(result);
              }
//doc9
         if (maxDoc>=8 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 380 &&  myevent.xbutton.y < 395) {
            //check null of ptr
             
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[8])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[8]);
           system(result);
              }

//doc10
         if (maxDoc>=9 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 410 &&  myevent.xbutton.y < 425) {
            //check null of ptr
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[9])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[9]);
           system(result);
              }
//doc11
         if (maxDoc>=10 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 440 &&  myevent.xbutton.y < 455) {
            //check null of ptr
             
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[10])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[10]);
           system(result);
              }
//doc12
         if (maxDoc>=11 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y >470 &&  myevent.xbutton.y < 485) {
            //check null of ptr
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[11])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[11]);
           system(result);
              }

//doc13
         if (maxDoc>=12 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 500 &&  myevent.xbutton.y < 515) {
            //check null of ptr
             
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[12])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[12]);
           system(result);
              } 
//doc14
         if (maxDoc>=13 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 530 &&  myevent.xbutton.y < 545) {
            //check null of ptr
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[13])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[13]);
           system(result);
              }
//doc15
         if (maxDoc>=14 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 560 &&  myevent.xbutton.y < 575) {
            //check null of ptr
             
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[14])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[14]);
           system(result);
              }
//doc16
         if (maxDoc>=15 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 590 &&  myevent.xbutton.y < 605) {
            //check null of ptr
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[15])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[15]);
           system(result);
              }
//doc17
         if (maxDoc>=16 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 620 &&  myevent.xbutton.y < 635) {
            //check null of ptr
           
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[16])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[16]);
           system(result);
              }
//doc18
         if (maxDoc>=17 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 650 &&  myevent.xbutton.y < 665) {
            //check null of ptr
           
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[17])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[17]);
           system(result);
              }
//doc19
         if (maxDoc>=18 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 680 &&  myevent.xbutton.y < 695) {
            //check null of ptr
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[18])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[18]);
           system(result);
              }
//doc20
         if (maxDoc>=20 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 710 &&  myevent.xbutton.y < 725) {
            //check null of ptr

            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[19])+1);//+1 for the zero-terminator
           //in real code you would check for errors in malloc here
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[19]);
           system(result);
              }

    
	     if (myevent.type==ButtonPress && myevent.xbutton.x >= 900   && myevent.xbutton.x < 925 && myevent.xbutton.y > 37 &&  myevent.xbutton.y < 62) {
        //shutdown
        }

//char *ffcmd="firefox",*chcmd="cheese", *wrcmd="libreoffice --writer", *calcmd= "libreoffice --calc", *impcmd="libreoffice --impress", *ubucmd="gnome-software",*syscmd= "gnome-system-monitor";

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 650   && myevent.xbutton.x < 770 && myevent.xbutton.y > 32 &&  myevent.xbutton.y < 67) {
        
           system("xdg-open /");  //650, 32, 120, 35
        }

    
        //APPS

         if (myevent.type==ButtonPress && myevent.xbutton.x >= 186   && myevent.xbutton.x < 323 && myevent.xbutton.y > 140 &&  myevent.xbutton.y < 155) {
        
           system("firefox");
        }

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 186   && myevent.xbutton.x < 323 && myevent.xbutton.y > 167 &&  myevent.xbutton.y < 183) {
        
           system("cheese");
        }


        if (myevent.type==ButtonPress && myevent.xbutton.x >= 186   && myevent.xbutton.x < 323 && myevent.xbutton.y > 200 &&  myevent.xbutton.y < 215) {
        
           system("gnome-system-monitor");
        }

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 186   && myevent.xbutton.x < 323 && myevent.xbutton.y > 228 &&  myevent.xbutton.y < 243) {
        
           system("libreoffice --writer");
        }

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 186   && myevent.xbutton.x < 323 && myevent.xbutton.y > 258 &&  myevent.xbutton.y < 274) {
        
           system("libreoffice --calc");
        }

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 186   && myevent.xbutton.x < 323 && myevent.xbutton.y > 290 &&  myevent.xbutton.y < 306) {
        
           system("libreoffice --impress");
        }

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 186   && myevent.xbutton.x < 323 && myevent.xbutton.y > 319 &&  myevent.xbutton.y < 334) {
        
           system("gnome-software");
        }


            break;
        case KeyPress: //Process key press - quit on q: 
            i = XLookupString(&myevent,text,10,&mykey,0);
            if (i==1 && text[0]=='q') done = 1;
            break;
            
        }
XDrawRectangle(mydisplay, mywindow, mygc, 20, 25, 1260, 50);
XDrawRectangle(mydisplay, mywindow, mygc, 1170, 37, 25, 25);
XDrawRectangle(mydisplay, mywindow, mygc, 1220, 37, 25, 25);

XDrawRectangle(mydisplay, mywindow, mygc, 650, 32, 120, 35);

//XDrawRectangle(mydisplay, mywindow, mygc, 980, 25, 150, 50);
//XDrawRectangle(mydisplay, mywindow, mygc, 1130, 25, 150, 50);
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

