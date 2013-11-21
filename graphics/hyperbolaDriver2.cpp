#include "hyperbola.h"
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

    printf("Enter center and a,b(bressenham first order)\n");
    scanf("%lf%lf%d%d",&p.x,&p.y,&a,&b);
    Hyperbola h1 = {a,b,p};
    outtextxy(p.x-a+XREF, -p.y+YREF+b, "bressenham first order");

    printf("Enter center and a,b(bressenham second order)\n");
    scanf("%lf%lf%d%d",&p.x,&p.y,&a,&b);
    Hyperbola h2 = {a,b,p};
    outtextxy(p.x-a+XREF, -p.y+YREF+b, "bressenham second order");

    h1.bressenFirstPlot(BLACK, 30);
    h2.bressenSecondPlot(BLACK, 40);

    getch();
    closegraph();
    return 0;
}
