#include<stdio.h>
#include "graphics.h"
#include "bezier.h"
#include "line.h"
int main()
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "");
    setbkcolor(WHITE);
    cleardevice();
    drawAxis(BLACK);
    setcolor(BLACK);

    double p[4][2];
    printf("Enter four end points\n");
    for(int i = 0; i<4; i++)
    {
        scanf("%lf%lf", &p[i][0], &p[i][1]);
    }
    drawBezier(p, BLACK, RED);
    getch();
    closegraph();
    return 0;
}
