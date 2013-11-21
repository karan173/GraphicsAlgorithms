#include "clipping.h"
#include<graphics.h>
#include<dos.h>
#include<conio.h>
int main()
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "");
    setbkcolor(WHITE);
    cleardevice();
    drawAxis(BLACK);
    int x1,y1,x2,y2;
    printf("Enter line coordinates\n");
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    Line l = Line{Point{x1,y1}, Point{x2,y2}};
    l.plotLineDDA(RED);

    Rect r;
    printf("Enter rectangle\n");
    scanf("%lf%lf%lf%lf",&r.min.x, &r.min.y, &r.max.x, &r.max.y);
    r.plotRect(GREEN);
    cohenSutherland(&r, &l, YELLOW);
    getch();
    closegraph();
    return 0;
}
