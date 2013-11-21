#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED
#include "line.h"
#include<dos.h>
typedef struct Polygon Poly;
/*
implemented as a linked list of points
note list will be either clockwise or anticlockwise
note the first and last points must be same -> cyclic
*/
struct Polygon
{
    Point p;
    Poly *next; //initialise to null
    void plotPoly(int color, char verbose)
    {
        if(verbose)
        {
            p.print();
            delay(2000);
        }
        if(!next)
        {
            return;
        }
        Line l = {p, next->p};
        l.plotLineDDA(color);
        next->plotPoly(color, verbose);
    }
};
#endif // POLYGON_H_INCLUDED
