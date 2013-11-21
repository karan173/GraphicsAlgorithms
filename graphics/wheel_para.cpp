#include "graphics.h"
#include "math.h"
#include <stdio.h>
#define XREF 320
#define YREF 240
#define NUM_SPOKES 4
typedef struct Point
{
    double x,y;
    void print()
    {
        printf("Point - {%lf %lf}\n", x, y);
    }
    void plot(int col)
    {
        putpixel(x,y,col);
    }
};
#define MAXP 10000
Point left[MAXP], right[MAXP];
int lctr = 0;
int rctr = 0;
int store = 1;
typedef struct Line
{
    Point p1, p2;
    void plot(int col)
    {
        setcolor(col);
        line(p1.x, p1.y, p2.x, p2.y);
    }
    void print()
    {
        printf("Line-\n");
        p1.print();
        p2.print();
    }
};

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
        //double y = p.x;
        Point p1 = {p.y+center.x, -p.x+center.y};
        Point p2 = {-p.y+center.x, -p.x+center.y};
        if(store)
        {
            left[rctr++] = p2;
            right[lctr++] = p1;
        }
        p1.plot(color);
        p2.plot(color);
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
};
void drawAxis(int col)
{
    Line l1 = {Point{XREF,0}, Point{XREF, 2*YREF}};
    Line l2 = {Point{0, YREF}, Point{2*XREF, YREF}};
    l1.plot(col);
    l2.plot(col);
}
void translateSingle(Point *pp, int dx, int dy)
{
    pp->x += dx;
    pp->y += dy;
}
void rotate2(Point *p, double theta)
{
    double Cos = cos(theta);
    double Sin = sin(theta);
    double x = p->x*Cos - p->y*Sin;
    double y = p->x*Sin + p->y*Cos;
    p->x = x;
    p->y = y;
}
void rotateSingle(Point *p, double theta, Point o)
{

    p->x -= o.x;
    p->y -= o.y;
    rotate2(p, theta);
    p->x += o.x;
    p->y += o.y;
}
typedef struct Ball
{
    Point o;
    double r;
    Line spokes[NUM_SPOKES];
    Point seeds[NUM_SPOKES];
    void plot(int cirCol, int spokeCol)
    {
        setcolor(cirCol);
        circle(o.x, o.y, r);
        setcolor(spokeCol);
        //draw lines
        for(int i = 0; i<NUM_SPOKES; i++)
        {
            spokes[i].plot(cirCol);
            //spokes[i].print();
            //delay(2000);
        }
        setfillstyle(SOLID_FILL, spokeCol);
        //floodfill(o.x, o.y, cirCol);
        for(int i = 0; i<NUM_SPOKES; i++)
        {
            floodfill(seeds[i].x, seeds[i].y, cirCol);
        }
    }
    void translate(int dx, int dy)
    {
        translateSingle(&o, dx, dy);
        //translate seeds
        for(int i = 0; i<NUM_SPOKES; i++)
        {
            translateSingle(&seeds[i], dx, dy);
        }
        //translate end points
        for(int i = 0; i<NUM_SPOKES; i++)
        {
            translateSingle(&spokes[i].p1, dx, dy);
            translateSingle(&spokes[i].p2, dx, dy);
        }
    }

    /*
    rotate about center
    */
    void rotate(double theta)
    {
        //center -> no need
        //rotate seeds
        for(int i = 0; i<NUM_SPOKES; i++)
        {
            rotateSingle(&seeds[i], theta, o);
        }
        //rotate end points
        for(int i = 0; i<NUM_SPOKES; i++)
        {
            rotateSingle(&spokes[i].p1, theta, o);
            rotateSingle(&spokes[i].p2, theta, o);
        }
    }
};
double getPos(double x, double r)
{
    return sqrt(r*r-x*x);
}
double getNeg(double x, double r)
{
    return -sqrt(r*r-x*x);
}
int main()
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "");
    Ball b;
    b.o = Point {XREF,YREF};
    b.r = 50;

    //spokes
    double k = 5;
    double x[] = {k, -k};
    double y[] = {k, -k};
    int ctr = 0;
    for(int i = 0; i<2; i++)
    {
        b.spokes[ctr++] = Line {Point{x[i]+XREF, YREF-getPos(x[i],b.r)}, Point{x[i]+XREF, YREF-getNeg(x[i],b.r)}};
    }
    for(int i = 0; i<2; i++)
    {
        Point p1 = Point {getPos(y[i],b.r)+XREF ,-y[i]+YREF };
        Point p2 = Point {getNeg(y[i],b.r)+XREF, -y[i]+YREF};
        b.spokes[ctr++] = Line {p1,p2};
    }
    b.seeds[0] = Point {XREF, -b.r/2+YREF};
    b.seeds[1] = Point {XREF, b.r/2+YREF};
    b.seeds[2] = Point {b.r/2+XREF, YREF};
    b.seeds[3] = Point {-b.r/2+XREF, YREF};
    drawAxis(WHITE);
    Parabola para = Parabola {Point{XREF,YREF+200}, 30};
    para.plotFirstOrder(YELLOW, 400);
    store = 0;
    b.translate(left[lctr-1].x - b.o.x, left[lctr-1].y - b.o.y);
    b.plot(RED, YELLOW);

    double theta =(3.142857*10)/180.0;

    while(1)
    {

        int iCtr = lctr-1;
        //left to right
        while(iCtr>0)
        {
            b.translate(left[iCtr].x - b.o.x, left[iCtr].y - b.o.y);
            b.rotate(theta);
            para.plotFirstOrder(YELLOW, 400);
            b.plot(RED, YELLOW);
            delay(0.05*abs(b.o.x-XREF));
            iCtr--;
            cleardevice();
        }
        iCtr=0;
        //right to right
        while(iCtr<rctr-1)
        {
            b.translate(right[iCtr].x - b.o.x, right[iCtr].y - b.o.y);
            b.rotate(theta);
            para.plotFirstOrder(YELLOW, 400);
            b.plot(RED, YELLOW);
            delay(0.05*abs(b.o.x-XREF));
            iCtr++;
            cleardevice();
        }
        theta*=-1;
        iCtr=rctr-1;
        //right to left
        while(iCtr>0)
        {
            b.translate(right[iCtr].x - b.o.x, right[iCtr].y - b.o.y);
            b.rotate(theta);
            para.plotFirstOrder(YELLOW, 400);
            b.plot(RED, YELLOW);
            delay(0.05*abs(b.o.x-XREF));
            iCtr--;
            cleardevice();
        }
        iCtr = 0;
        //left to left
        while(iCtr<lctr-1)
        {
            b.translate(left[iCtr].x - b.o.x, left[iCtr].y - b.o.y);
            b.rotate(theta);
            para.plotFirstOrder(YELLOW, 400);
            b.plot(RED, YELLOW);
            delay(0.05*abs(b.o.x-XREF));
            iCtr++;
            cleardevice();
        }
        theta*=-1;
    }

    getch();
    closegraph();
    return 0;
}
