#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#define p(x,y,z) printf(x,y,z)
#define e "\x1b"
struct termios t,r;
int s=-1;
void c(){
tcsetattr(0,2, &t);
p(e"[?1049l"e"[?25h%d\n",s,0);
}
main(){
tcgetattr(0, &t);
atexit(c);
signal(15,exit);
signal(2,exit);
r=t;
r.c_lflag&=-11;
tcsetattr(0,2,&r);
fcntl(0,4,fcntl(0,3)|2048);
struct winsize z;
ioctl(1,21523,&z);
int w=z.ws_col,h=z.ws_row,p=w/2,x=8*w/2,y=16,i,d=1,g=0,o;
p(e"[?1049h"e"[2J"e"[?25l"e"[%d;%dH"e"[s",h,0);
for(;;){
i=getchar();
p=p+(i=='a'?-2:i=='d'?2:0);
p=p<8?w:p>w?8:p;
x+=d/3;
if(x/8<1||x/8>w){d=-d;p("\a",0,0);}
y+=g/4;
g++;
o=-4+p-x/8;
if(y/8>h-1){d-=o*2-1;s++;g=-g+abs(o)*2;if(abs(o)>4)exit(0);}
p(e"[u%*s",p,"(((())))");
p(e"[%d;%dHO",y/8,x/8);
p(e"[0;%dH%d",w/2,s+1);
fflush(0);
usleep(50000/2);
p(e"[2J",0,0);
}
}
