#include <termios.h>
#define e "\x1b["
struct termios t,r;
int c(){tcsetattr(0,2, &t);puts(e"?25h");}
main(){
atexit(c);
tcgetattr(0, &t);
r=t;
r.c_lflag&=-11;
tcsetattr(0,2,&r);
fcntl(0,4,2048);
int w=80,h=24,p=40,x=319,y=40,i,d=1,g=0,o,s=0;
for(;;){
i=getchar();
p=p+(i=='a'?-2:i=='d'?2:0);
p=p<0?0:p>w-6?w-6:p;
x+=d/3;
y+=g/4;
g++;
o=3+p-x/8;
if(y/8>h){
puts("\a");
s++;
d-=o*3+1;
g=abs(d/2)-g+1;
g=g>-9?-9:g;
if(abs(o)>4)break;}
printf(e"2J"e"?25l"e"3;38H%d"e"24;%dH%s",s,p,"_______");
if(x>8&&x/8<w)printf(e"%d;%dHo",y/8,x/8);
fflush(0);
usleep(25000);}}
