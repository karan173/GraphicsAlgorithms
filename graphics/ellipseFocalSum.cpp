#include<stdio.h>
#include<graphics.h>
#include "ellipse.h"
#include "math.h"
#include "line.h"
#define MAXN 5000
Point quad[4][MAXN];
int ctr = 0;
struct Ellipse2
{
    void plot4waySymmetry(Point p, int color, Point center)
    {
        int dx[] = {1,1,-1,-1};
        int dy[] = {1,-1,-1,1};
        for(int i = 0; i<4; i++)
        {
            Point q;
            q.initPoint(p.x*dx[i] + center.x, p.y*dy[i] + center.y);
            quad[i][ctr] = q;
            //q.plotPoint(color);
        }
        ctr++;
    }
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
};

/*
we store all points of 4 quadrants in 4 different arrays and in clockwise order
*/
void swap(int i, int a, int b)
{
    Point t = quad[i][a];
    quad[i][a] = quad[i][b];
    quad[i][b] = t;
}
void reverse(int i)
{
    int lCtr = 0, rCtr = ctr-1;
    while(lCtr < rCtr)
    {
        swap(i, lCtr++, rCtr--);
    }
}
int main()
{
    /* request autodetection */
    int gdriver = DETECT, gmode;
    /* initialize graphics mode */
    initgraph(&gdriver, &gmode, "");
    drawAxis(WHITE);
    double a = 200, b=100;
    Ellipse2 ell = {a,b,Point{0,0}};
    double focalDist = sqrt(a*a-b*b);
    Point f1 = Point{focalDist, 0};
    Point f2 = Point{-focalDist, 0};

    ell.plotSecondOrder(YELLOW); //generate points
    //points of second and 4th quadrants are in anticlockwise order, reverse it
    reverse(1);
    reverse(3);
    for(int i = 0; i<4; i++)
    {
        for(int j = 0; j<ctr; j++)
        {

            Line l1 = Line{quad[i][j], f1};
            Line l2 = Line{quad[i][j], f2};
            l1.plotLineDDA(YELLOW);
            l2.plotLineDDA(YELLOW);
            delay(10);
            l1.plotLineDDA(BLACK);
            l2.plotLineDDA(BLACK);
            quad[i][j].plotPoint(RED);
            drawAxis(WHITE);
        }
    }
    return 0;
}
