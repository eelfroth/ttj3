#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>
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
fcntl(0,4,2048);
int w=80,h=24,p=w/2,x=8*w/2,y=40,i,d=1,g=0,o;
p(e"[?1049h"e"[2J"e"[?25l"e"[%d;%dH"e"[s",h,0);
for(;;){
i=getchar();
p=p+(i=='a'?-2:i=='d'?2:0);
p=p<8?8:p>w?w:p;
x+=d/3;
y+=g/4;
g++;
o=-3+p-x/8;
if(y/8>h-1){p("\a",0,0);d-=o*3+1;s++;g=abs(d/2)-g+1;g=g>-16?-16:g;if(abs(o)>4)exit(0);}
p(e"[u%*s",p,"_______");
if(x/8>0&&x/8<w)p(e"[%d;%dHo",y/8,x/8);
p(e"[0;%dH%d",w/2,s+1);
fflush(0);
usleep(25000);
p(e"[2J",0,0);
}
}
