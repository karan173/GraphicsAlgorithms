#include<stdio.h>
#include<graphics.h>
#include "circle.h"
#include "line.h"
#include "fill.h"
#include "2dTransformation.h"
void rotateTranslateAll(Point p[NUM_VERTICES], double theta, int dx)
{
    for(int i = 0; i<NUM_VERTICES; i++)
    {
        translateSingle(&p[i], dx, 0);
        rotateSingle(&p[i], theta);
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
    //seedFill4(o, RED, RED);
    double theta =  0;    //-(3.142857*10)/180.0;
    int dx = 5;
    do
    {
//        printf("old\n");
//        for(int i = 0; i<16; i++)
//        {
//            p[i].print();
//        }
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
        translateSingle(&o, dx, 0);
        rotateTranslateAll(p, theta, dx);
//        printf("new\n");
//        for(int i = 0; i<16; i++)
//        {
//            p[i].print();
//        }
        c.bressenPlot(BLACK);
        inCircle.bressenPlot(BLACK);
        c.center = o;
        c.bressenPlot(RED);
        inCircle.center = o;
        inCircle.bressenPlot(RED);
    }
    while(1);
    getch();
    closegraph();
    return 0;
}
