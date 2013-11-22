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
};
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
        for(int i = 0; i<NUM_SPOKES;i++)
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
    b.o = Point{XREF,YREF};
    b.r = 100;

    //spokes
    double k = 5;
    double x[] = {k, -k};
    double y[] = {k, -k};
    int ctr = 0;
    for(int i = 0; i<2; i++)
    {
        b.spokes[ctr++] = Line{Point{x[i]+XREF, YREF-getPos(x[i],b.r)}, Point{x[i]+XREF, YREF-getNeg(x[i],b.r)}};
    }
    for(int i = 0; i<2; i++)
    {
        Point p1 = Point{getPos(y[i],b.r)+XREF ,-y[i]+YREF };
        Point p2 = Point{getNeg(y[i],b.r)+XREF, -y[i]+YREF};
        b.spokes[ctr++] = Line{p1,p2};
    }
    b.seeds[0] = Point{XREF, -b.r/2+YREF};
    b.seeds[1] = Point{XREF, b.r/2+YREF};
    b.seeds[2] = Point{b.r/2+XREF, YREF};
    b.seeds[3] = Point{-b.r/2+XREF, YREF};
    b.plot(RED, YELLOW);

    //drawAxis(WHITE);
    double dx = 5;
    double theta = (3.142857*10)/180.0;
    do
    {

        b.plot(RED, YELLOW);
        b.translate(dx, 0);
        b.rotate(theta);
        delay(50);
        cleardevice();
    }while(1);
	getch();
    closegraph();
    return 0;
}
