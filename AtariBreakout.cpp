#include<graphics.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
int a=1366,b=700;
//int a=640,b=480;
void background(int color,int height,int width)
{
    int a=getcolor();
    setfillstyle(1,color);
    bar(0,0,height,width);
    setfillstyle(1,a);
}
struct brick
{
    int posx;
    int posy;
    int c;
};
void printbrick(struct brick br)
{
    setcolor(br.c);
    setfillstyle(5,br.c);//
    bar(br.posx,br.posy,br.posx+a/15,br.posy+b/12);
    rectangle(br.posx,br.posy,br.posx+a/15,br.posy+b/12);
}
void printbrd(int x,int y,int c)
{
    setcolor(c);
    setfillstyle(1,c);//
    bar(x,y,x+(a/5),y+(b/18));
    //rectangle(br.posx,br.posy,br.posx+a/15,br.posy+b/12);
}
void printball(int x,int y,int c)
{
    setcolor(c);
    setfillstyle(1,c);
    circle(x,y,b/36);
    floodfill(x,y,c);
}
void breakout(int x,int i,struct brick *br,int bg)
{
    int j;
    for(j=0;j<a;j++)
        {
            if(br[i*a+j].posx+(a/15)>=x   &&br[i*a+j].posx<=x)
            {
                br[i*a+j].c=bg;
                printbrick(br[i*a+j]);
            }

        }
}
int checkcolor(int x,int i,struct brick *br)
{
    int j;
    for(j=0;j<a;j++)
        {
            if(br[i*a+j].posx+(a/15)>=x   &&br[i*a+j].posx<=x)
            {
                return(br[i*a+j].c);
                //printbrick(bricks[i*a+j]);
            }

        }
}
void showscore(int sc,int back)
{
    char score[80];
    sprintf(score,"SCORE: %d",sc);
    setfillstyle(1,back);
    //bar(3*a/4,b/48,a,b/12);
    setcolor(15);
    settextstyle(0,0,0);
    outtextxy(3.3*a/4,b/24,score);

    if(sc==60)
    {
        setcolor(4);
        settextstyle(0,0,8);
        outtextxy(a/4,b/4+b/24,"Perfect Score");
        getch();
        exit(1);
    }
}
void gameover()
{
    setfillstyle(1,10);
    //bar(a/4,b/4,3*a/4,3*b/4);
    setcolor(4);
    settextstyle(0,0,8);
    outtextxy(a/4+a/12,b/4+b/24,"Game Over");
    getch();
}
void paused()
{
    setcolor(15);
    settextstyle(0,0,0);
    outtextxy(0.95*a/2,b/24,"[Paused]");
}
void unpaused(int back)
{
    setcolor(back);
    settextstyle(0,0,0);
    outtextxy(0.95*a/2,b/24,"[Paused]");
}
void lives(int l,int back)
{
    int i;
    setfillstyle(1,back);
    bar(a/24,b/48,a/24+(5*b/24),b/12);
    for(i=0;i<5;i++)
    {
         setcolor(4);
         circle(a/24+b/48+i*b/24,b/24,b/48);
         if(l>0)
          {
             setfillstyle(1,4);
             floodfill(a/24+b/48+i*b/24,b/24,4);
             l--;
          }
    }
}
//void reflection(int x[],int y[],int r,int d[])
//{

//}
int main()
{
    printf("Enter the resolution of window : ");
    scanf("%d %d",&a,&b);
    int score=0,l=5;
    //target:
    int back=0,brclr[3]={4,2,14},i,j,k;
    int pposx=0,pposy=7*b/8,pclr=9;
    float ballx[2]={(a/5)+1,(a/5)},bally[2]={3*b/4,(3*b/4)-1},ballc=15,ballr=b/36;
    float dy,dx,cos,sin;
    int dir[2]={1,1};//dir[horizontal,vertical]
    char ch;



    initwindow(a,b,"Atari Breakout");
    background(back,a,b);
    struct brick *bricks;
    bricks=(struct brick*)malloc(4*a*sizeof(struct brick));
    for(i=0;i<4;i++)
    {
        for(j=0;j<a;j++)
        {
            bricks[i*a+j].posx=j*a/15;
            bricks[i*a+j].posy=(2+i)*(b/12);
            bricks[i*a+j].c=brclr[rand()%3];
            printbrick(bricks[i*a+j]);
        }
    }
    printball(ballx[1],bally[1],ballc);
    printbrd(pposx,pposy,pclr);
    showscore(score,back);
    lives(l,back);
    setcolor(15);
    line(0,b/12,a,b/12);

    getch();
    while(1)
    {

        printball(ballx[1],bally[1],back);
        dy=bally[1]-bally[0];
        dx=ballx[1]-ballx[0];
        cos=dx/sqrt((dy*dy)+(dx*dx));
        sin=dy/sqrt((dy*dy)+(dx*dx));
        bally[0]=bally[1];
        ballx[0]=ballx[1];
        bally[1]=bally[0]+(5*sin);
        ballx[1]=ballx[0]+(5*cos);
        for(i=1;i<5;i++)
            if(((bally[1]-ballr))/((2+i)*b/12)<1.001  &&  checkcolor(ballx[1],i-1,bricks)!=back)
                {
                    dir[1]=-1;
                    breakout(ballx[1],i-1,bricks,back);
                    score++;
                    showscore(score,back);
                }
        if((bally[1]-ballr)<b/12)
        {
            dir[1]=-1;

        }
        if((ballx[1]-ballr)<0)
            dir[0]=-1;
        if((ballx[1]+ballr)>a)
            dir[0]=-1;
        if((bally[1]+ballr)>(pposy-5)  && pposx-b/18<=ballx[1] && (pposx+a/5+b/18)>=ballx[1])
        {
            dir[1]=-1;
            if((ballx[1]-ballr)>(pposx+a/5) || (ballx[1]+ballr)<pposx)
            {
                dir[0]=-1;
            }

        }
        if((bally[1]+ballr)>b)
            {
                l--;
                if(l>0)
                {
                     lives(l,back);
                     ballx[0]=a/5+1;
                     ballx[1]=a/5;
                     bally[0]=3*b/4;
                     bally[1]=(3*b/4)-1;
                     dir[1]=1;
                     dir[0]=1;
                     printball(ballx[1],bally[1],15);
                     getch();
                     goto target;

                }
                else
                {
                    gameover();
                    exit(1);
                }
            }
         //   reflection(ballx,bally,ballr,dir);
        bally[1]=bally[0]+dir[1]*(5*sin);
        ballx[1]=ballx[0]+dir[0]*(5*cos);
        dir[1]=1;
        dir[0]=1;
        printball(ballx[1],bally[1],15);
        target:
        if(kbhit()!=0)
        {
        ch=getch();
        if(ch=='a' || ch=='A')
        {
            printbrd(pposx,pposy,back);
            if(pposx-(a/10)>=0)
                pposx-=a/10;
            printbrd(pposx,pposy,pclr);
        }
        else if(ch=='d' || ch=='D')
        {
            printbrd(pposx,pposy,back);
            if(pposx+(a/5)+(a/10)<=a)
                pposx+=a/10;
            printbrd(pposx,pposy,pclr);
        }
        else if(ch=='x' || ch=='X')
        {
            exit(1);
        }
        }
        else if(ch=='p' || ch=='P')
         {
             paused();
             getch();
             unpaused(back);
             ch='y';
         }
        delay(10);
    }
    return 0;
}
