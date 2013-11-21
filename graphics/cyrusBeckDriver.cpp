#include<stdio.h>
#include<graphics.h>
#include "clipping.h"
/*
-30 70
60 100
80 -10
20 -20
-80 0
-30 70
Enter line
-150 100
150 20

-30 70
60 100
80 -10
20 -20
-80 0
-30 70
Enter line
*/
int main()
{
	int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "");
    setbkcolor(WHITE);
    cleardevice();
    drawAxis(BLACK);
    int n;
    Poly *poly = NULL;
    printf("Enter n for convex polygon\n");
    scanf("%d", &n);
    printf("Enter points in clockwise/anticlockwise order\n");
    for(int i = 0; i<n; i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        Point p = Point{x,y};
        Poly *newPoly = (Poly *)malloc(sizeof(Poly));
        *newPoly = Poly{p, poly};
        poly = newPoly;
    }
    poly->plotPoly(BLACK, 0);
    printf("Enter line\n");
    Line l;
    scanf("%lf%lf%lf%lf", &l.p1.x, &l.p1.y, &l.p2.x, &l.p2.y);
    l.plotLineDDA(BLUE);
    cyrusBeck(poly, &l, YELLOW);
    getch();
    closegraph();
    return 0;

}
