#include<graphics.h>
#include "parabola.h"
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

    Parabola p;
    printf("Enter center and a for parabola(mid point-first order)\n");
    scanf("%lf%lf%lf", &p.center.x, &p.center.y, &p.a);
    p.plotFirstOrder(BLACK, 70);
    outtextxy(p.center.x+XREF, -p.center.y+YREF, "mid point first order");

    printf("Enter center and a for parabola(mid point-second order)\n");
    scanf("%lf%lf%lf", &p.center.x, &p.center.y, &p.a);
    p.plotSecondOrder(BLACK, 70);
    outtextxy(p.center.x+XREF, -p.center.y+YREF, "mid point second order");

    printf("Enter center and a for parabola(bressenham-first order)\n");
    scanf("%lf%lf%lf", &p.center.x, &p.center.y, &p.a);
    p.bressenFirstPlot(BLACK, 70);
    outtextxy(p.center.x+XREF, -p.center.y+YREF, "bressenham-first order");

    printf("Enter center and a for parabola(bressenham-second order)\n");
    scanf("%lf%lf%lf", &p.center.x, &p.center.y, &p.a);
    p.bressenSecondPlot(BLACK, 70);
    outtextxy(p.center.x+XREF, -p.center.y+YREF, "bressenham-second order");

	getch();
    closegraph();
    return 0;
}
