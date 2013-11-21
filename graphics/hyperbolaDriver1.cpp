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

    printf("Enter center and a,b(midpoint first order)\n");
    scanf("%lf%lf%d%d",&p.x,&p.y,&a,&b);
    Hyperbola h1 = {a,b,p};
    outtextxy(p.x+XREF, -p.y+YREF+b, "midpoint first order");
    h1.plotFirstOrder(BLACK, 40);

    printf("Enter center and a,b(midpoint second order)\n");
    scanf("%lf%lf%d%d",&p.x,&p.y,&a,&b);
    Hyperbola h2 = {a,b,p};
    outtextxy(p.x-a+XREF, -p.y+YREF+b, "midpoint second order");
    h2.plotSecondOrder(BLACK, 40);

    getch();
    closegraph();
    return 0;
}
