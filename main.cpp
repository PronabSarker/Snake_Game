#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <windows.h>

int main()
{
    int i,x[100],y[100],rx,ry,l,d=2;
    int page=0;
    char ara[100], ins[500];
    srand(time(NULL));
    ///creating graphics window
    DWORD scwidth = GetSystemMetrics(SM_CXSCREEN);
    DWORD scheight = GetSystemMetrics(SM_CYSCREEN);
    initwindow(scwidth, scheight, "The Snake Game");

    x[0]= scwidth/2;
    y[0]= scheight/2;

    l=5;///initial snake length

    ///updating the snake
    for(i=1; i<l; i++)
    {
        x[i]= x[i-1]-16;
        y[i]= y[0];
    }
     ///food coordinates
    rx=rand()%scwidth;
    ry=rand()%scheight;
    if(rx<=(scwidth/2)) rx+=50;
    else rx-=50;
    if(ry<=(scheight/2)) ry+=50;
    else ry-=50;
    ///welcome screen
    setcolor(GREEN);
    settextstyle(BOLD_FONT, HORIZ_DIR, 5);
    sprintf(ins, "WELCOME TO SNAKE GAME");
    outtextxy(50,100,ins);
    setcolor(CYAN);
    sprintf(ins,"INSTRUCTIONS");
    outtextxy(50,200,ins);
    sprintf(ins, "PRESS ARROW KEYS TO MOVE SNAKE.");
    setcolor(BLUE);
    outtextxy(50, 300, ins);
    setcolor(RED);
    sprintf(ins, "WHEN THE SNAKE DIES PREES ENTER TO CLOSE THE GAME. ENJOY :)");
    outtextxy(50,400,ins);
    setcolor(WHITE);
    sprintf(ins, "PREES ANY KEY TO START THE GAME.");
    outtextxy(50,500,ins);

    getch();
    cleardevice();



    while(1)
    {
        ///double buffering
        setactivepage(page);
        setvisualpage(1-page);

        cleardevice();

        ///creating border
        setfillstyle(SOLID_FILL,1);
        bar(0,30,scwidth,47);///UP
        bar(0,47,17,scheight);///left
        bar(17,scheight-45,scwidth, scheight-28);///DOWNN
        bar(scwidth-20,47, scwidth, scheight);///right

        ///creating food
        setfillstyle(SOLID_FILL,2);
        bar(rx-8,ry-8, rx+8, ry+8);



        ///moving the snake
        for(i=l; i>0; i--)
        {
            x[i]= x[i-1];
            y[i]= y[i-1];
        }
        ///updating the head
        if(d==0)
            x[0]= x[0]-16;///left`
        else if(d==1)
            y[0]= y[0]-16; ///up
        else if(d==2)
            x[0]= x[0]+16;///right
        else if(d==3)
            y[0]= y[0]+16; ///down

        ///terminating condition
        if(getpixel(x[0], y[0])==1) break;

        ///updating direction
        if(GetAsyncKeyState(VK_RIGHT)&& d!=0)
            d=2;
        else if(GetAsyncKeyState(VK_UP) && d!=3)
            d=1;
        else if(GetAsyncKeyState(VK_LEFT) && d!=2)
            d=0;
        else if(GetAsyncKeyState(VK_DOWN) && d!=1)
        d=3;

        ///food taken??
        if(getpixel(x[0], y[0])==2)
        {
            rx=rand()%scwidth;
            ry=rand()%scheight;
            if(rx<=(scwidth/2)) rx+=50;
            else rx-=50;
            if(ry<=(scheight/2)) ry+=50;
            else ry-=50;
            setfillstyle(SOLID_FILL,2);
            bar(rx-8,ry-8, rx+8, ry+8);
            l=l+1;///increase snake length
        }

        delay(100-((l-5)*3));///snake speed
        page=1-page;///double buffering
        ///displaying the snake
        setfillstyle(SOLID_FILL,1);
        for(i=0;i<l; i++)
            bar(x[i]-8, y[i]-8, x[i]+8, y[i]+8);
        ///printing score on graphics window
        sprintf(ara,"%d", l-5);
        setcolor(YELLOW);
        settextstyle(BOLD_FONT, HORIZ_DIR,3);
        outtextxy(scwidth-100,7, ara);
    }
    printf("Score %d", l-5);
    while(!GetAsyncKeyState(VK_RETURN));
    closegraph();
    return 0;
}

