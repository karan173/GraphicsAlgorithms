#include "circle.h"
#include "line.h"
#include<conio.h>
int main()
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "");
    setbkcolor(WHITE);
    cleardevice();
    drawAxis(BLACK);
    setcolor(BLACK);

    Circle c1,c2,c3,c4;
    Point p;
    int r;

    printf("Enter center and radius(midpoint first order)\n");
    scanf("%lf%lf%d",&p.x,&p.y,&r);
    c1 = {p, r};
    outtextxy(p.x-r+XREF, -p.y+YREF+r, "midpoint first order");

    printf("Enter center and radius(midpoint second order)\n");
    scanf("%lf%lf%d",&p.x,&p.y,&r);
    c2 = {p, r};
    outtextxy(p.x-r+XREF, -p.y+YREF+r, "midpoint second order");

    printf("Enter center and radius(bressenham first order)\n");
    scanf("%lf%lf%d",&p.x,&p.y,&r);
    c3 = {p, r};
    outtextxy(p.x-r+XREF, -p.y+YREF+r, "bressenham first order");

    printf("Enter center and radius(bressenham second order)\n");
    scanf("%lf%lf%d",&p.x,&p.y,&r);
    c4 = {p, r};
    outtextxy(p.x-r+XREF, -p.y+YREF+r, "bressenham second order");

    c1.plotFirstOrder(BLACK);
    c2.plotSecondOrder(BLACK);
    c3.bressenPlot(BLACK);
    c4.bressenSecondPlot(BLACK);


    getch();
    closegraph();
    return 0;
}
