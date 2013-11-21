#include "graphics.h"
#include<stdio.h>
#include "polygon.h"
#include "fill.h"
int main()
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "");
    setbkcolor(WHITE);
    cleardevice();

    setcolor(BLACK);

    int n;
    Poly *poly = NULL;
    printf("Enter n\n");
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
    printf("Enter boundary color\n");
    int bCol;
    scanf("%d", &bCol);
    poly->plotPoly(bCol, 0);
    printf("Enter interior point\n");
    int inX, inY;
    scanf("%d%d", &inX, &inY);
    printf("Enter fill color\n");
    int fCol;
    scanf("%d", &fCol);
    Point in = {inX, inY};
    seedFill4(in, fCol, bCol);
    drawAxis(BLACK);
	getch();
    closegraph();
    return 0;
}
