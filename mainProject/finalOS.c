/*
*                               Basic X program:
*
*       This is a very simple X program.  It shows the basics needed to get the
*       simplest X program working.   Compile as:
*               
                    cc FinalOS.c -lX11 -o FinalOS
*
*     
*/


#include<stdio.h>
#include<stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include<sys/utsname.h>
#include <limits.h>
#include<string.h>
#include <assert.h>
#include<time.h>

//*******************************************
char *subst(char *str, int left)
{
char substring[strlen(str)-left+1];
  int c=left;
int sub_i=0;
 while (c <strlen(str)) {
      substring[sub_i] = str[c];
     c++;
     sub_i++;
   }
   substring[sub_i] = '\0';
 //  printf("%s",substring);
str=substring;
return str;
}

//*******************************************


char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
   delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    { //changes to resolve parsing
        if (a_delim == *tmp &&(*(tmp+1)!=' '))
        {  
            count++;
            last_comma = tmp;
        }
       tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);
        
        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}
//*****************************trim function 
char *trim(char *str)
{
char ptr[strlen(str)+1];
int i,j=0;
for(i=0;str[i]!='\0';i++)
{
if (str[i] != ' ' && str[i] != '\t') 
ptr[j++]=str[i];
} 
ptr[j]='\0';
str=ptr;
return str;
}

//******************************


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
//documents
            FILE* fp;
            char* command;
            char* line;
            int i=0,maxDoc=0;
            line = malloc(200 * sizeof(char));
            command = malloc(200 * sizeof(char));
            strcpy(command,"ls Documents");

            fp = popen(command,"r");

            const char ptr[20][30];

            while(fgets(line,  INT_MAX, fp))

                     {
                        strcpy(ptr[i],line);
                        i++;
                        if(i>20) break;
                     }
        maxDoc=i;
    
//CALENDAR

        FILE* fp3;
        char* command3;
        char* line3;
        const char ptr2[6][30];
        int n=0;

 line3 = malloc(200 * sizeof(char));
 command3 = malloc(200 * sizeof(char));
 strcpy(command3,"cal");

 fp3 = popen(command3,"r");
 
 while((fgets(line3,  INT_MAX, fp3)))
 { 
    strcpy(ptr2[n],line3);
    n++;
 }

int maxCal=n;

  //END CALENDAR



    int myscreen;
    unsigned long myforeground, mybackground;
    char text[10];
    int done;
    char *sysn = uname_pointer.sysname, *noden = uname_pointer.nodename, *release= uname_pointer.release, *version = uname_pointer.version, *machine= uname_pointer.machine  ;
    char *sysHead= "SYSTEM INFORMATION",*sys = "SYSTEM NAME : ", *node= "NODENAME : ", *releas = "RELEASE : ", *ver = "VERSION : ", *mac = "MACHINE : "; 
    char *docHead= "DOCUMENTS";
    char *appHead= "APPLICATIONS",*firefox = "FIREFOX", *cheese = "CHEESE", *writer = "LibreOffice Writer", *sysMonitor = "SYSTEM MONITOR", *calc = "LibreOffice Calc",*impress = "LibreOffice Impress",*UbuSoft= "UBUNTU SOFTWARE";
    char *diskHead = "DISK INFORMATION";
    char *calendar = "CALENDAR";
    char *mail = "MAIL";
    char *gmail = "GMAIL", *iitrmail = "IITR MAIL";
    char *news= "NEWS";
    char *news1="HINDUSTAN TIMES", *news2="TIMES OF INDIA", *news3= "THE HINDU", *news4= "TIMES NOW";
    char *suspend = "S", *shutdown = "P";

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
    char *dayDT= s;

        /* Create a window - not displayed yet however: */
    mywindow = XCreateSimpleWindow(mydisplay,DefaultRootWindow(mydisplay),


    myhint.x,myhint.y,myhint.width,myhint.height,5,myforeground,mybackground);


////***************DISKS******************//////
FILE* fp2;
 char* command2;
 char* line2;
 line2 = malloc(200 * sizeof(char));
 command2 = malloc(200 * sizeof(char));
 strcpy(command2,"pydf");

 fp2 = popen(command2,"r");
 fgets(line2,  INT_MAX, fp2);
 char** disc_result=malloc(200*sizeof(char));
 
int disc_i=0;
 while((fgets(line2,  INT_MAX, fp2)))
 {  char** tokens;
     
     tokens = str_split(line2, ' ');
  if (tokens)
    {  
       int token_i=0;
       while(trim(*(tokens+token_i))=="\0"){token_i++;}
       disc_result[disc_i]="Disc :"; 
       disc_i++;
       char * subs = *(tokens+token_i);
       disc_result[disc_i]= subs; 
       disc_i++;
       token_i++;
       while(trim(*(tokens+token_i))=="\0"){token_i++;}
       disc_result[disc_i]="Size :"; disc_i++;
       disc_result[disc_i]=*(tokens+token_i); 
       disc_i++;
       token_i++; 
       
        }

 }
 int max_disc=disc_i;

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

int disc_y= 400;
for(int disc_i=0;disc_i<max_disc;disc_i++){

 XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,    //disk
                        mygc,30,disc_y,disc_result[disc_i],strlen(disc_result[disc_i]));

  disc_y=disc_y+20;
}
                
                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,1173,50,suspend,strlen(suspend));

                 XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,1225,50,shutdown,strlen(shutdown));

                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,1172,415,gmail,strlen(gmail));
                 

                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,1172, 486, iitrmail,strlen(iitrmail));
                

        

                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,1180,120,calendar,strlen(calendar));
                XDrawLine(mydisplay,mywindow,mygc, 1175,125, 1230,125);


                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,1175,336,mail,strlen(mail));
                XDrawLine(mydisplay,mywindow,mygc, 1170,340,1200,340);

                
                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,1040,210,news,strlen(news));
                XDrawLine(mydisplay,mywindow,mygc, 1030,215,1080,215);
                 
                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,1000,300,news1,strlen(news1));

                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,1000,400,news2,strlen(news2));

                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,1000,500,news3,strlen(news3));

                XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,1000,600,news4,strlen(news4));

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


                     //documents
            int ycor= 150;

    int k;
                    for(k=0;k<maxDoc;k++){
                   
                        XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,350,ycor,ptr[k],strlen(ptr[k])-1);
                        ycor=ycor+30;
                        }  
   ycor=160;
                    for(k=0;k<maxCal;k++){
                   
                        XDrawImageString(myevent.xexpose.display,myevent.xexpose.window,
                        mygc,1135,ycor,ptr2[k],strlen(ptr2[k])-1);
                        ycor=ycor+20;
                        }                         
                
            break;

        case MappingNotify: /* Process keyboard mapping changes: */
            XRefreshKeyboardMapping(&myevent);
            break;
        case ButtonPress: /* Process mouse click - output Hi! at mouse: */
        printf("You pressed a button at (%i,%i)\n",  myevent.xbutton.x,myevent.xbutton.y); 

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 1139   && myevent.xbutton.x < 1265 && myevent.xbutton.y > 471 &&  myevent.xbutton.y < 492) {
        
            system("xdg-open https://www.iitr.ac.in/webmail.html");
            
            }

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 1139   && myevent.xbutton.x < 1265 && myevent.xbutton.y > 404 &&  myevent.xbutton.y < 419) {
        
            system("xdg-open http://www.gmail.com/");
            
            }

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 984   && myevent.xbutton.x < 1125 && myevent.xbutton.y > 286 &&  myevent.xbutton.y < 305) {
        
            system("xdg-open http://www.hindustantimes.com/");
            
            }

         if (myevent.type==ButtonPress && myevent.xbutton.x >= 984   && myevent.xbutton.x < 1125 && myevent.xbutton.y > 387 &&  myevent.xbutton.y < 403) {
        
            system("xdg-open http://timesofindia.indiatimes.com/topic/official-website");
            
            }

         if (myevent.type==ButtonPress && myevent.xbutton.x >= 984   && myevent.xbutton.x < 1125 && myevent.xbutton.y > 487 &&  myevent.xbutton.y < 504) {
       
            system("xdg-open http://www.thehindu.com/");
            
            }

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 984   && myevent.xbutton.x < 1125 && myevent.xbutton.y > 587 &&  myevent.xbutton.y < 605) {
        
            system("xdg-open http://www.timesnow.tv");
            
            }

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 1133   && myevent.xbutton.x < 1278 && myevent.xbutton.y > 148 &&  myevent.xbutton.y < 276) {
      
            system("zenity --calendar &");
            
            }

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 900   && myevent.xbutton.x < 925 && myevent.xbutton.y > 37 &&  myevent.xbutton.y < 62) {
       
            system("DISPLAY=:0 gnome-session-quit --logout --no-prompt");

            }
//doc1 
         if (maxDoc>=1 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 140 &&  myevent.xbutton.y < 155) {
          
          char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[0])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[0]);
           system(result);
           // printf("You pressed a button at (%i,%i)\n",myevent.xbutton.x,myevent.xbutton.y);      
             

         }
//doc2
         if (maxDoc>=2 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 170 &&  myevent.xbutton.y < 185) {
           
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[1])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           
           strcat(result,ptr[1]);
           system(result);
              }

//doc3
         if ( maxDoc>=3 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 200 &&  myevent.xbutton.y < 215) {
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[2])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[2]);
           system(result);
              }

//doc4
         if (maxDoc>=4 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 230 &&  myevent.xbutton.y < 245) {
             
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[3])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[3]);
           system(result);
              }
//doc5
         if (maxDoc>=4 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 260 &&  myevent.xbutton.y < 275) {
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[4])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[4]);
           system(result);
              }

//doc6
         if (maxDoc>=5 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 290 &&  myevent.xbutton.y < 305) {
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[5])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[5]);
           system(result);
              }

//doc7
         if (maxDoc>=6 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 320 &&  myevent.xbutton.y < 335) {
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[6])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[6]);
           system(result);
              }  

//doc8
         if (maxDoc>=7 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 350 &&  myevent.xbutton.y < 365) {
             
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[7])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[7]);
           system(result);
              }
//doc9
         if (maxDoc>=8 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 380 &&  myevent.xbutton.y < 395) {
             
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[8])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[8]);
           system(result);
              }

//doc10
         if (maxDoc>=9 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 410 &&  myevent.xbutton.y < 425) {
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[9])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[9]);
           system(result);
              }
//doc11
         if (maxDoc>=10 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 440 &&  myevent.xbutton.y < 455) {
             
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[10])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[10]);
           system(result);
              }
//doc12
         if (maxDoc>=11 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y >470 &&  myevent.xbutton.y < 485) {
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[11])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[11]);
           system(result);
              }

//doc13
         if (maxDoc>=12 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 500 &&  myevent.xbutton.y < 515) {
             
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[12])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[12]);
           system(result);
              } 
//doc14
         if (maxDoc>=13 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 530 &&  myevent.xbutton.y < 545) {
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[13])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[13]);
           system(result);
              }
//doc15
         if (maxDoc>=14 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 560 &&  myevent.xbutton.y < 575) {
             
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[14])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[14]);
           system(result);
              }
//doc16
         if (maxDoc>=15 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 590 &&  myevent.xbutton.y < 605) {
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[15])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[15]);
           system(result);
              }
//doc17
         if (maxDoc>=16 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 620 &&  myevent.xbutton.y < 635) {
           
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[16])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[16]);
           system(result);
              }
//doc18
         if (maxDoc>=17 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 650 &&  myevent.xbutton.y < 665) {
           
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[17])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[17]);
           system(result);
              }
//doc19
         if (maxDoc>=18 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 680 &&  myevent.xbutton.y < 695) {
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[18])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[18]);
           system(result);
              }
//doc20
         if (maxDoc>=20 && myevent.type==ButtonPress && myevent.xbutton.x >= 333   && myevent.xbutton.x < 478 && myevent.xbutton.y > 710 &&  myevent.xbutton.y < 725) {
      
            
           char *result = malloc(strlen("xdg-open Documents/")+strlen(ptr[19])+1);//+1 for the zero-terminator
           strcpy(result,"xdg-open Documents/");
           strcat(result,ptr[19]);
           system(result);

              }

    
	     if (myevent.type==ButtonPress && myevent.xbutton.x >= 1171   && myevent.xbutton.x < 1194 && myevent.xbutton.y > 40 &&  myevent.xbutton.y < 60) {
        //suspend
            system("systemctl suspend");
        }

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 1223   && myevent.xbutton.x < 1244 && myevent.xbutton.y > 40 &&  myevent.xbutton.y < 61) {
        //shutdown
            system("systemctl shutdown");
        }


    
        //APPS

         if (myevent.type==ButtonPress && myevent.xbutton.x >= 186   && myevent.xbutton.x < 323 && myevent.xbutton.y > 140 &&  myevent.xbutton.y < 155) {
        
           system("firefox &");
        }

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 186   && myevent.xbutton.x < 323 && myevent.xbutton.y > 167 &&  myevent.xbutton.y < 183) {
        
           system("cheese &");
        }


        if (myevent.type==ButtonPress && myevent.xbutton.x >= 186   && myevent.xbutton.x < 323 && myevent.xbutton.y > 200 &&  myevent.xbutton.y < 215) {
        
           system("gnome-system-monitor &");
        }

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 186   && myevent.xbutton.x < 323 && myevent.xbutton.y > 228 &&  myevent.xbutton.y < 243) {
        
           system("libreoffice --writer &");
        }

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 186   && myevent.xbutton.x < 323 && myevent.xbutton.y > 258 &&  myevent.xbutton.y < 274) {
        
           system("libreoffice --calc &");
        }

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 186   && myevent.xbutton.x < 323 && myevent.xbutton.y > 290 &&  myevent.xbutton.y < 306) {
        
           system("libreoffice --impress &");
        }

        if (myevent.type==ButtonPress && myevent.xbutton.x >= 186   && myevent.xbutton.x < 323 && myevent.xbutton.y > 319 &&  myevent.xbutton.y < 334) {
        
           system("gnome-software &");
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

