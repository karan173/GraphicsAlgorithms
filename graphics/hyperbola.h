#ifndef HYPERBOLA_H_INCLUDED
#define HYPERBOLA_H_INCLUDED
#include "point.h"
typedef struct Hyperbola Hyperbola;
struct Hyperbola
{
    double a,b;
    Point center;
    void initHyperbola(double _a, double _b, Point c)
    {
        a = _a, b = _b;
        center = c;
    }
    void plotFirstOrder(int color, double XMAX)
    {
        XMAX+=a;

        Point p = {a, 0};
        double aa = a*a;
        double bb = b*b;
        double aa2 = 2*aa;
        double bb2 = 2*bb;
        double d = bb*a + bb/4.0 - aa;
        double fx = bb2*a, fy = 0;
        plot4waySymmetry(p, color, center);
        while(fx > fy && p.x<=XMAX)
        {
            p.y ++;
            fy += aa2;
            if(d>=0)
            {
                d -= aa*(2*p.y+1);
            }
            else
            {
                p.x++;
                fx += bb2;
                d += bb2*p.x - aa*(2*p.y+1);
            }
            plot4waySymmetry(p, color, center);
        }
        d = bb*(p.x+1)*(p.x+1) - aa*(p.y+0.5)*(p.y+0.5) - aa*bb;
        while(p.x<=XMAX)
        {
            p.print();
            p.x++;
            if(d < 0)
            {
                d += bb*(1+2*p.x);
            }
            else
            {
                p.y++;
                d += bb*(1+2*p.x) - aa2 * p.y;
            }
            plot4waySymmetry(p, color, center);
        }
    }

    void plotSecondOrder(int color, double XMAX)
    {
        XMAX+=a;
        Point p = {a, 0};
        double aa = a*a;
        double bb = b*b;
        double aa2 = 2*aa;
        double bb2 = 2*bb;
        double d = bb*a + bb/4.0 - aa;
        double fx = bb2*a, fy = 0;
        double deltaN = -3 * aa;
        double deltaNE = deltaN + bb2*(a+1);
        plot4waySymmetry(p, color, center);
        while(fx > fy && p.x<=XMAX)
        {
            p.y ++;
            fy += aa2;
            if(d>=0) //N
            {
                d += deltaN;
                deltaN -= aa2;
                deltaNE -= aa2;
            }
            else //NE
            {
                p.x++;
                fx += bb2;
                d += deltaNE;
                deltaN -= aa2;
                deltaNE += bb2 - aa2;
            }
            plot4waySymmetry(p, color, center);
        }
        d = bb*(p.x+1)*(p.x+1) - aa*(p.y+0.5)*(p.y+0.5) - aa*bb;
        double deltaE = bb*(2*p.x + 3);
        deltaNE = deltaE - aa2 * (p.y+1);

        while(p.x<=XMAX)
        {
            p.x++;
            if(d < 0)  //E
            {
                d += deltaE;
                deltaE += bb2;
                deltaNE += bb2;
            }
            else //NE
            {
                p.y++;
                d += deltaNE;
                deltaE += bb2;
                deltaNE += bb2 - aa2;
            }
            plot4waySymmetry(p, color, center);
        }
    }

    void bressenFirstPlot(int color, double XMAX)
    {
        XMAX+=a;
        Point p = {a, 0};
        double aa = a*a;
        double bb = b*b;
        double fx = bb*2*a, fy = 0;
        double d = 2*aa - bb - 2*a*bb;
        while(fx > fy && p.x<=XMAX)
        {
            plot4waySymmetry(p, color, center);
            if(d <= -bb/2 )
            {
                d += 2*aa*(2*p.y+3);
            }
            else
            {
                d += 2*aa*(2*p.y+3) - 4*bb*(p.x+1);
                p.x++;
                fx += bb*2;
            }
            p.y++;
            fy += aa*2;
        }
        d = 2*bb*(p.x+1)*(p.x+1) - 2*aa*bb - aa*(p.y*p.y + (p.y+1)*(p.y+1));
        while(p.x<=XMAX)
        {
            plot4waySymmetry(p, color, center);
            if(d<=-aa/2)
            {
                d += 2*bb*(2*p.x+3);
            }
            else
            {
                d += 2*bb*(2*p.x+3) - 4*aa*(p.y+1);
                p.y++;
            }
            p.x++;
        }
    }

    void bressenSecondPlot(int color, double XMAX)
    {
        XMAX+=a;
        Point p = {a, 0};
        double aa = a*a;
        double bb = b*b;
        double fx = bb*2*a, fy = 0;
        double d = 2*aa - bb - 2*a*bb;
        double delN = 6*aa;
        double delNE = 6*aa - 4*bb*(a+1);
        while(fx > fy && p.x<=XMAX)
        {
            plot4waySymmetry(p, color, center);
            if(d <= -bb/2) //N
            {
                d += delN;
                delNE += 4*aa;
            }
            else //NE
            {
                d += delNE;
                delNE += 4*(aa-bb);
                p.x++;
                fx += bb*2;
            }
            delN += 4*aa;
            p.y++;
            fy += aa*2;
        }
        d = 2*bb*(p.x+1)*(p.x+1) - 2*aa*bb - aa*(p.y*p.y + (p.y+1)*(p.y+1));
        delNE = 2*bb*(2*p.x+3) - 4*aa*(p.y+1);
        double delE = 2*bb*(2*p.x+3);
        while(p.x<=XMAX)
        {
            plot4waySymmetry(p, color, center);
            if(d<=-aa/2) //E
            {
                d += delE;
                delNE += 4*bb;
            }
            else //NE
            {
                d += delNE;
                delNE += 4*(bb-aa);
                p.y++;
            }
            delE += 4*bb;
            p.x++;
        }
    }
};


#endif // HYPERBOLA_H_INCLUDED
