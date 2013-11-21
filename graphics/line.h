#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED
#include "point.h"
#include<stdio.h>
#include<dos.h>
typedef struct Line Line;
struct Line
{
    Point p1, p2;
    void initLine(Point _p1, Point _p2)
    {
        p1 = _p1;
        p2 = _p2;
        if(p1.x > p2.x)
        {
            Point t = p1;
            p1 = p2;
            p2 = t;
        }
    }
    void print()
    {
        printf("Line-\n");
        p1.print();
        p2.print();
    }
    void plotLineDDA(int color)
    {
        double dx = p2.x - p1.x;
        double dy = p2.y - p1.y;
        double steps = (abs(dx)>abs(dy)) ? abs(dx) : abs(dy);
        double xIncr = dx/steps;
        double yIncr = dy/steps;
        Point p = p1;
        p.plotPoint(color);
        for(int i = 0; i<steps; i++)
        {
            p.x += xIncr;
            p.y += yIncr;
            p.plotPoint(color);
        }
    }
    /*
    for abs(slope) <=1
    */
    void plotLineMidPt(int color)
    {
        double delY = p2.y - p1.y;
        double delX = p2.x - p1.x;
        //assert(delX >= delY);
        double d = delY - delX/2;
        Point p = p1;
        while(p.x <= p2.x)
        {
            p.plotPoint(color);
            if(d<=0)
            {
                d += delY;
            }
            else
            {
                d += delY - delX;
                p.y++;
            }
            p.x ++;
        }
    }
    /*
    for abs(slope) b/w 0 and 1
    */
    void plotLineBressen(int color)
    {
        double delY = p2.y - p1.y;
        double delX = p2.x - p1.x;
       // assert(delX >= delY);
        double d = 2*delY - delX;
        Point p = p1;
        while(p.x <= p2.x)
        {
            p.plotPoint(color);
            if(d<=0)
            {
                d += 2*delY;
            }
            else
            {
                d += 2*(delY - delX);
                p.y++;
            }
            p.x ++;
        }
    }

};
/*utility functions*/
void drawAxis(int color)
{
    Line xAxis, yAxis;
    Point p[] = {{-XREF, 0}, {XREF, 0}, {0, YREF}, {0,-YREF}};
    xAxis.initLine(p[0], p[1]);
    yAxis.initLine(p[2], p[3]);

    xAxis.plotLineDDA(color);
    yAxis.plotLineDDA(color);
}
Point midPoint(Line *l)
{
    Point p = {(l->p1.x + l->p2.x)/2 , (l->p1.y+l->p2.y)/2 };
    return p;
}
#endif // LINE_H_INCLUDED
