#include "ellipse.h"
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


    Point p;
    int a,b;

    printf("Enter center and a,b(midpoint first order)\n");
    scanf("%lf%lf%d%d",&p.x,&p.y,&a,&b);
    ELLIPSE e1 = {a,b,p};
    outtextxy(p.x-a+XREF, -p.y+YREF+b, "midpoint first order");

    printf("Enter center and a,b(midpoint second order)\n");
    scanf("%lf%lf%d%d",&p.x,&p.y,&a,&b);
    ELLIPSE e2 = {a,b,p};
    outtextxy(p.x-a+XREF, -p.y+YREF+b, "midpoint second order");

    printf("Enter center and a,b(bressenham first order)\n");
    scanf("%lf%lf%d%d",&p.x,&p.y,&a,&b);
    ELLIPSE e3 = {a,b,p};
    outtextxy(p.x-a+XREF, -p.y+YREF+b, "bressenham first order");

    printf("Enter center and a,b(bressenham second order)\n");
    scanf("%lf%lf%d%d",&p.x,&p.y,&a,&b);
    ELLIPSE e4 = {a,b,p};
    outtextxy(p.x-a+XREF, -p.y+YREF+b, "bressenham second order");

    e1.plotFirstOrder(BLACK);
    e2.plotSecondOrder(BLACK);
    e3.bressenFirstPlot(BLACK);
    e4.bressenSecondPlot(BLACK);

    getch();
    closegraph();
    return 0;
}
