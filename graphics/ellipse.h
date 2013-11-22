#ifndef ELLIPSE_H_INCLUDED
#define ELLIPSE_H_INCLUDED
#include<stdio.h>
#include<dos.h>
#include "point.h"
typedef struct Ellipse ELLIPSE;
struct Ellipse
{
    double a,b;
    Point center;
    void initEllipse(double _a, double _b, Point c)
    {
        a = _a, b = _b;
        center = c;
    }
    void plotFirstOrder(int color)
    {
        Point p = {0, b};
        double aa = a*a;
        double bb = b*b;
        double aa2 = 2*aa;
        double bb2 = 2*bb;
        double d = bb + aa/4.0 - aa*b;
        double fx = 0, fy = b*aa2;
        plot4waySymmetry(p, color, center);
        while(fx < fy)
        {
            p.x ++;
            fx += bb2;
            if(d<0)
            {
                d += bb*(2*p.x+1);
            }
            else
            {
                p.y--;
                fy -= aa2; //fy represents mod fy, since y decreases its mod decreases
                d += bb*(2*p.x+1) - aa2 * p.y;
            }

            plot4waySymmetry(p, color, center);
        }
        d = bb * (p.x + 0.5) * (p.x+0.5) + aa * (p.y-1) * (p.y-1) - aa*bb;
        while(p.y > 0)
        {
            p.y--;
            if(d >= 0)
            {
                d += aa*(1-2*p.y);
            }
            else
            {
                p.x++;
                d += aa*(1-2*p.y) + bb2*p.x;
            }

            plot4waySymmetry(p, color, center);
        }
    }

    void plotSecondOrder(int color)
    {
        Point p = {0, b};
        double aa = a*a;
        double bb = b*b;
        double aa2 = aa*2;
        double bb2 = bb*2;
        double d = bb + aa/4.0 - aa*b;
        double fx = 0, fy = b*aa2;
        plot4waySymmetry(p, color, center);
        double deltaE = 3*bb;
        double deltaSE = deltaE - aa2*(b-1);
        while(fx < fy)
        {
            p.x ++;
            fx += bb2;
            if(d<0)
            {
                d += deltaE;
                deltaE += bb2;
                deltaSE += bb2;
            }
            else
            {
                p.y--;
                fy -= aa2;
                d += deltaSE;
                deltaE += bb2;
                deltaSE += aa2 + bb2;
            }
            plot4waySymmetry(p, color, center);
        }
        d = bb * (p.x + 0.5) * (p.x+0.5) + aa * (p.y-1) * (p.y-1) - aa*bb;
        double deltaS = aa*(3-2*p.y);
        deltaSE = aa*(3-2*p.y) + bb2 *(p.x+1);
        while(p.y > 0)
        {
            p.y--;
            if(d >= 0)
            {
                d += deltaS;
                deltaS += aa2;
                deltaSE += aa2;
            }
            else
            {
                p.x++;
                d += deltaSE;
                deltaS += aa2;
                deltaSE += aa2 + bb2;
            }
            plot4waySymmetry(p, color, center);
        }
    }


    void bressenFirstPlot(int color)
    {
        Point p = {0,b};
        double aa = a*a;
        double bb = b*b;
        double d = -2*bb + aa*(2*b-1);
        double fx = 0, fy = b*aa*2;
        while(fx < fy)
        {
            plot4waySymmetry(p, color, center);
            if(d>=-aa/2) //east
            {
                d+= -2*bb*(2*p.x+3);
            }
            else //south east
            {
                d+= -2*bb*(2*p.x+3) + 4*aa*(p.y-1);
                p.y--;
                fy -= aa*2;
            }
            p.x++;
            fx += bb*2;
        }
        d = -2*aa*(bb-(p.y-1)*(p.y-1)) + bb*p.x*p.x + bb*(p.x+1)*(p.x+1);

        while(p.y >= 0)
        {
            plot4waySymmetry(p, color, center);
            if(d >= bb/2) //south
            {
                d +=  -2*aa*(2*p.y-3);
            }
            else //south east
            {
                d += -2*aa*(2*p.y-3) + 4*bb*(p.x+1);
                p.x++;
            }
            p.y--;
        }

    }

    void bressenSecondPlot(int color)
    {
        Point p = {0,b};
        double aa = a*a;
        double bb = b*b;
        double d = -2*bb + aa*(2*b-1);
        double fx = 0, fy = b*aa*2;
        double delE = -6*bb;
        double delSE = delE + 4*aa*(b-1);
        while(fx < fy)
        {
            plot4waySymmetry(p, color, center);
            if(d>=-aa/2) //east
            {
                d += delE;
                delSE += -4*bb;
            }
            else //south east
            {
                d+= delSE;
                delSE += -4*(bb+aa);
                p.y--;
                fy -= aa*2;
            }
            delE += -4*bb;
            p.x++;
            fx += bb*2;
        }
        d = -2*aa*(bb-(p.y-1)*(p.y-1)) + bb*p.x*p.x + bb*(p.x+1)*(p.x+1);
        double delS = -2*aa*(2*p.y-3);
        delSE = delS + 4*bb*(p.x+1);
        while(p.y >= 0)
        {
            plot4waySymmetry(p, color, center);
            if(d >= bb/2) //south
            {
                d +=  delS;
                delSE += 4*aa;
            }
            else
            {
                d += delSE;
                delSE += 4*(bb+aa);
                p.x++;
            }
            delS += 4*aa;
            p.y--;
        }
    }
};

#endif // ELLIPSE_H_INCLUDED
