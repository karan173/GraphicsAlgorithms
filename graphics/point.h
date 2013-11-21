#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED
/*
Coordinate system has origin at (XREF, YREF)
*/
#include<graphics.h>
#include<stdio.h>
#include<dos.h>
#define XREF 320
#define YREF 240
#define ROUND(x) (int)((x)+0.5)
typedef struct Point Point;
struct Point
{
    double x,y;
    void initPoint(double xx, double yy)
    {
        x = xx, y = yy;
    }

    void plotPoint(int color)
    {

        int xx = ROUND(x+XREF);
        int yy = ROUND(-y+YREF); //- because we want conventional coordinate system
        putpixel(xx, yy, color);
    }

    int getColor()
    {
        int xx = ROUND(x+XREF);
        int yy = ROUND(-y+YREF); //- because we want conventional coordinate system
        return getpixel(xx,yy);
    }

    /* for debugging */
    void print()
    {
        printf("Point - {%lf %lf}\n", x, y);
    }
};
/* utility functions */
void plot4waySymmetry(Point p, int color, Point center)
{
    int dx[] = {1,1,-1,-1};
    int dy[] = {1,-1,1,-1};
    for(int i = 0; i<4; i++)
    {
        Point q;
        q.initPoint(p.x*dx[i] + center.x, p.y*dy[i] + center.y);
        q.plotPoint(color);
    }
}

#endif // POINT_H_INCLUDED
