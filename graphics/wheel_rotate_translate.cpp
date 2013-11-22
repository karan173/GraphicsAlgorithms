#include<stdio.h>
#include<graphics.h>
#include "circle.h"
#include "line.h"
#include "fill.h"
#include "2dTransformation.h"

void translateAll(Point p[NUM_VERTICES], int dx)
{
    for(int i = 0; i<NUM_VERTICES; i++)
    {
        translateSingle(&p[i], dx, 0);
    }
}
void rotateAll(Point p[NUM_VERTICES], double theta)
{
    for(int i = 0; i<NUM_VERTICES; i++)
    {
        rotateSingle(&p[i], theta);
    }
}

int main()
{
    /* request autodetection */
    int gdriver = DETECT, gmode;
    /* initialize graphics mode */
    initgraph(&gdriver, &gmode, "");
    outtextxy(100, 100, "wheel");  //for writing text
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
    double theta = -(3.142857*10)/180.0;
    int dx = 5;
    int netDx = 0;
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
        translateAll(p, -netDx);
        netDx+=dx;


        //delay(1000);
        rotateAll(p, theta);
        translateSingle(&o, dx, 0);
        translateAll(p, netDx);

        c.bressenPlot(BLACK);
        inCircle.bressenPlot(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
        floodfill(inCircle.center.x+XREF, (-inCircle.center.y+YREF), BLACK);
        c.center = o;
        c.bressenPlot(RED);
     //   seedFill4(inCircle.center, BLACK, BLACK);
        inCircle.center = o;
        inCircle.bressenPlot(RED);
        setfillstyle(SOLID_FILL, RED);
        floodfill(inCircle.center.x+XREF, (-inCircle.center.y+YREF), RED);
        drawAxis(WHITE);
    }
    while(1);
    getch();
    closegraph();
    return 0;
}
