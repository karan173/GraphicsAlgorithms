#include "point.h"
#ifndef PARABOLA_H_INCLUDED
#define PARABOLA_H_INCLUDED

typedef struct Parabola Parabola;

struct Parabola
{
    Point center;
    double a;
    void initParabola(double _a, Point c)
    {
        a = _a;
        center = c;
    }

    void plotSymmetry(Point p, int color)
    {
//        Point p1 = {p.x + center.x, p.y + center.y};
//        Point p2 = {p.x + center.x, -p.y + center.y};
        Point p1 = {p.y+center.y, p.x+center.x};
        Point p2 = {-p.y+center.y, p.x+center.x};
        p1.plotPoint(color);
        p2.plotPoint(color);
    }

    void plotFirstOrder(int color, double XMAX)
    {
        Point p = {0,0};
        double d = (2*a) - 1;
        plotSymmetry(p, color);
        while(p.y<= (2*a*1.0))
        {
            if(d<0)
            {
                d+= 4*a-3-2*p.y;
                p.x++;
                p.y++;
            }
            else
            {
                d+= -3 - 2*p.y;
                p.y++;
            }
            plotSymmetry(p, color);
        }

        d = (4.0*a*(p.x+1) - (p.y+0.5)*(p.y+0.5) );

        while( p.x<XMAX )
        {
            if(d<0)
            {
                d+= 4*a;
                p.x++;
            }
            else
            {
                d+= 4.0*a - 2 - 2.0*p.y ;
                p.x++;
                p.y++;
            }
            plotSymmetry(p, color);
        }
    }

    void plotSecondOrder(int color, double XMAX)
    {
        Point p = {0,0};
        double d = (2*a) - 1;
        double delNE = 4*a-3-2*p.y;
        double delN = -3 - 2*p.y;
        plotSymmetry(p, color);
        while(p.y<= (2*a*1.0))
        {
            if(d<0) //NE
            {
                d += delNE;
                p.x++;
                p.y++;
            }
            else //N
            {
                d += delN;
                p.y++;
            }
            delNE -=2;
            delN -= 2;
            plotSymmetry(p, color);
        }

        d = (4.0*a*(p.x+1) - (p.y+0.5)*(p.y+0.5) );
        delNE = 4.0*a - 2 - 2.0*p.y;
        double delE = 4*a;
        while( p.x<XMAX )
        {
            if(d<0) //E
            {
                d+= delE;
                delNE -= 2;
                p.x++;
            }
            else //NE
            {
                d+= delNE;
                delNE -= 2;
                p.x++;
                p.y++;
            }
            plotSymmetry(p, color);
        }
    }

    void bressenFirstPlot(int color, int XMAX)
    {
        Point p = {0,0};
        double d = 1 - (2*a);

        while( p.y<= (2*a) )
        {
            plotSymmetry(p, color);
            if(d>0)
            {
                d+= 3 + 2*p.y - 4*a;
                p.x++;
                p.y++;
            }
            else
            {
                d+= 3 + 2*p.y;
                p.y++;
            }
        }

        d = ((p.y+0.5)*(p.y+0.5) - 4*a*(p.x+1));

        while( p.x < XMAX )
        {
            if(d>0)
            {
                d+= (-4*a);
                p.x++;
            }
            else
            {
                d+= 2 + 2*p.y - 4*a;
                p.x++;
                p.y++;
            }
            plotSymmetry(p, color);
        }
    }

    void bressenSecondPlot(int color, int XMAX)
    {
        Point p = {0,0};
        double d = 1 - (2*a);
        double delNE = 3 + 2*p.y - 4*a;
        double delN = 3 + 2*p.y;
        while( p.y<= (2*a) )
        {
            plotSymmetry(p, color);
            if(d>0) //NE
            {
                d+= delNE;
                p.x++;
            }
            else //N
            {
                d+= delN;
            }
            p.y++;
            delN += 2;
            delNE += 2;
        }

        d = ((p.y+0.5)*(p.y+0.5) - 4*a*(p.x+1));
        double delE = -4*a;
        delNE = 2 + 2*p.y - 4*a;
        while( p.x < XMAX )
        {
            if(d>0)
            {
                d+= delE;
            }
            else
            {
                d+= delNE;
                p.y++;
                delNE += 2;
            }
            p.x++;
            plotSymmetry(p, color);
        }
    }
};


#endif // PARABOLA_H_INCLUDED
