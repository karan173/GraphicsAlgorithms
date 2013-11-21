#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include "line.h"

int main(void)
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "");
    setbkcolor(WHITE);
    cleardevice();
    drawAxis(BLACK);
    setcolor(BLACK);
    int x1, y1, x2, y2;
    printf("Enter line1(midpoint)\n");
    scanf("%d%d%d%d",&x1,&y1,&x2, &y2);
    Line l1 = Line{Point{x1, y1}, Point{x2,y2}};
    outtextxy(x1+XREF,-y1+YREF,"midpoint algorithm");

    printf("Enter line2(dda)");
    scanf("%d%d%d%d",&x1,&y1,&x2, &y2);
    Line l2 = Line{Point{x1, y1}, Point{x2,y2}};
    outtextxy(x1+XREF,-y1+YREF,"dda algorithm");

    printf("Enter line2(bressenham)");
    scanf("%d%d%d%d",&x1,&y1,&x2, &y2);
    Line l3 = Line{Point{x1, y1}, Point{x2,y2}};
    outtextxy(x1+XREF,-y1+YREF,"bressenham algorithm");

    l1.plotLineMidPt(BLACK);
    l2.plotLineDDA(BLACK);
    l3.plotLineBressen(BLACK);
    getch();
    closegraph();
    return 0;

}
