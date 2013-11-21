#include<graphics.h>
#include<conio.h>
#include "polygon.h"
#include "rectangle.h"
#include "clipping.h"
int main()
{
    initwindow(700, 700);
    drawAxis(WHITE);
    Point p[] = {Point{-20,50}, Point{50,200}, Point{120,50}, Point{50, -200}, Point{-20, 50} };
    int n = sizeof(p)/ sizeof(Point);
    Poly *head = NULL;
    // i was doing this - http://stackoverflow.com/questions/5136393/for-loop-local-variables-in-c
    for(int i = 0; i<n; i++)
    {
        Poly *x = (Poly *) malloc (sizeof(Poly));
        *x = {p[i], head};
        head = x;
    }
    head->plotPoly(YELLOW,0);
    Rect r = {Point{0,0}, Point{100, 150} };
    r.plotRect(BLUE);
    Poly *op = sutherlandHodgeman(head, &r);
    op->plotPoly(RED,1);
    delay(2000);
	return 0;
}
