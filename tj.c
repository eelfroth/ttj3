#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>
#define p(x,y,z) printf(x,y,z)
struct termios t,r;
void c(){
tcsetattr(0,2, &t);
p("\x1b[?1049lbye\n",0,0);}
main(){
tcgetattr(0, &t);
atexit(c);
signal(15,exit);
signal(2,exit);
r=t;
r.c_lflag&=-11;
tcsetattr(0,2,&r);
fcntl(0,4,fcntl(0,3)|2048);
int x=0;
p("\x1b[?1049h\x1b[2J",0,0);
for(;;){
int i=getchar();
x+=i=='a'?-1:i=='d'?1:0;
p("%*s\r",x,"#######");
fflush(0);
usleep(10000);
p("\x1b[2J",0,0);
}
}
