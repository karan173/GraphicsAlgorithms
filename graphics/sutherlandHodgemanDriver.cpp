#include<graphics.h>
#include<conio.h>
#include "polygon.h"
#include "rectangle.h"
#include "clipping.h"
/*
Enter n for polygon
5
Enter points of polygon in clockwise/anticlockwise order\n
-20 50
50 200
120 50
50 -200
-20 50
Enter rectangle
0 -100 100 150
*/
int main()
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "");
    setbkcolor(WHITE);
    cleardevice();
    drawAxis(BLACK);

    int n;
    Poly *head = NULL;
    printf("Enter n for polygon");
    scanf("%d", &n);
    printf("Enter points of polygon in clockwise/anticlockwise order\n");
    for(int i = 0; i<n; i++)
    {
        Point p;
        scanf("%lf%lf",&p.x,&p.y);
        Poly *x = (Poly *) malloc (sizeof(Poly));
        *x = {p, head};
        head = x;
    }
    head->plotPoly(MAGENTA,0);
    Rect r;
    printf("Enter rectangle\n");
    scanf("%lf%lf%lf%lf",&r.min.x, &r.min.y, &r.max.x, &r.max.y);
    r.plotRect(BLUE);
    Poly *op = sutherlandHodgeman(head, &r);
    op->plotPoly(YELLOW,0);
    getch();
	return 0;
}
