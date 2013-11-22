#include<stdio.h>
#include<graphics.h>
#include "circle.h"
#include "line.h"
#include "fill.h"
#include "2dTransformation.h"
void rotateAll(Point p[NUM_VERTICES], double theta)
{
    double pointMatrix[N][NUM_VERTICES];
    double rslt[N][NUM_VERTICES];
    for(int i = 0; i<NUM_VERTICES; i++)
    {
        pointMatrix[0][i] = p[i].x;
    }
    for(int i = 0; i<NUM_VERTICES; i++)
    {
        pointMatrix[1][i] = p[i].y;
    }
    for(int i = 0; i<NUM_VERTICES; i++)
    {
        pointMatrix[2][i] = 1;
    }
    rotate(pointMatrix, theta, rslt);
    for(int i = 0; i<NUM_VERTICES; i++)
    {
        p[i].x = rslt[0][i];
    }
    for(int i = 0; i<NUM_VERTICES; i++)
    {
        p[i].y = rslt[1][i];
    }
}
int main()
{
    /* request autodetection */
    int gdriver = DETECT, gmode;
    /* initialize graphics mode */
    initgraph(&gdriver, &gmode, "");

    drawAxis(WHITE);
    Point o = {0,0};
    Circle c = {o,130};
    c.bressenPlot(RED);
    Point p[NUM_VERTICES]=
    {
        Point{129,10}, Point{28,10},
        Point{-28,10}, Point{-129,10},
        Point{129,-10}, Point{28,-10},
        Point{-28,-10}, Point{-129,-10},
        Point{10,129}, Point{10,28},
        Point{10,-129}, Point{10, -28},
        Point{-10,129}, Point{-10,28},
        Point{-10,-129}, Point{-10, -28}
    };
    Circle inCircle = {o, 30};
    inCircle.bressenPlot(RED);
    seedFill4(o, RED, RED);
    double theta = -(3.142857*10)/180.0;

    do
    {
        for(int i = 0; i<16; i+=2)
        {
            Line l = Line {p[i], p[i+1]};
            l.plotLineDDA(YELLOW);
        }
        delay(15);
        for(int i = 0; i<16; i+=2)
        {
            Line l = Line {p[i], p[i+1]};
            l.plotLineDDA(BLACK);
        }
        rotateAll(p, theta);
        c.bressenPlot(RED);

    }
    while(1);
    getch();
    closegraph();
    return 0;
}
