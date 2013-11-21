#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED
#include "point.h"
#include<stdio.h>
#include<dos.h>
typedef struct Circle Circle;
struct Circle
{
    Point center;
    double r;

    void initCircle(Point _orig, double _r)
    {
        center = _orig;
        r = _r;
    }
    void print()
    {
        printf("Circle- r=%f\nOrigin-", r);
        center.print();
    }
    /*
    Circle has 8 way symmetry
    */
    void plotSymmetry(Point p, int color)
    {
        plot4waySymmetry(p, color, center);
        plot4waySymmetry(Point{p.y, p.x}, color, center);
    }
    /*
    plots in top half of first quad and uses symmetry
    */
    void plotFirstOrder(int color)
    {
        center.plotPoint(color);
        Point p;
        p.initPoint(0, r);
        plotSymmetry(p, color);
        double d = 5.0/4 - r;
        while(p.x < p.y)
        {
            p.x++;
            if(d<0)
            {
                d += 2*p.x + 1;
            }
            else
            {
                p.y--;
                d += 2*(p.x - p.y) + 1;
            }
            plotSymmetry(p, color);
        }
    }

    void plotSecondOrder(int color)
    {
        center.plotPoint(color);
        Point p;
        p.initPoint(0, r);
        plotSymmetry(p, color);
        double d = 5.0/4 - r;
        int deltaE = 3;
        double deltaSE = -2*r+5;
        while(p.x < p.y)
        {
            p.x++;
            if(d<0)
            {
                d += deltaE;
                deltaE += 2;
                deltaSE += 2;
            }
            else
            {
                p.y--;
                d += deltaSE;
                deltaE += 2;
                deltaSE += 4;
            }
            plotSymmetry(p, color);
        }
    }

    void bressenPlot(int color)
    {
        center.plotPoint(color);
        Point p = {0, r};
        double d = 3 - 2*r;
        while(p.x <= p.y)
        {
            plotSymmetry(p, color);
            if(d<=0)
            {
                d += 4*p.x + 6;
            }
            else
            {
                d += 4*(p.x-p.y) + 10;
                p.y--;
            }
            p.x++;
        }
    }

    void bressenSecondPlot(int color)
    {
        center.plotPoint(color);
        Point p = {0, r};
        double d = 3 - 2*r;
        double deltaE = 6, deltaSE = 10 - 4*r;
        while(p.x <= p.y)
        {
            plotSymmetry(p, color);
            if(d<=0)
            {
                d += deltaE;
                deltaE += 4;
                deltaSE += 4;
            }
            else
            {
                d += deltaSE;
                deltaE += 4;
                deltaSE += 8;
                p.y--;
            }
            p.x++;
        }
    }
};
#endif // CIRCLE_H_INCLUDED
