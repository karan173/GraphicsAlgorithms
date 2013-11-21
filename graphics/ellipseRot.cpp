#include "graphics.h"
#include "ellipse.h"
#include "math.h"
Point stored2[10000];
Point locus[10000];
int storePoints(Point *stored2)
{
    int nctr = 0;
    //first quad clockewise
    for(int i = 0; i<ctr; i++)
    {
        stored2[nctr++] = stored[i];
    }
    //4th quad clockwise
    for(int i = ctr-1; i>=0; i--)
    {
        stored2[nctr++] = stored[i];
        stored2[nctr-1].y*=-1;
    }
    //3rd
    for(int i = 0; i<ctr; i++)
    {
        stored2[nctr++] = stored[i];
        stored2[nctr-1].y*=-1;
        stored2[nctr-1].x*=-1;
    }
    //2nd
    for(int i = ctr-1; i>=0; i--)
    {
        stored2[nctr++] = stored[i];
        stored2[nctr-1].x*=-1;
    }
    return nctr;
}

void plotEll(Point center, int n, Point *a, int col)
{
    for(int i = 0; i<n; i++)
    {
        a[i].x+=center.x, a[i].y+=center.y;
        a[i].plotPoint(col);
        a[i].x-=center.x, a[i].y-=center.y;
    }
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

int main()
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "");
    setcolor(YELLOW);
    //circle
    double r = 120;
    ellipse(XREF,YREF,0,360,r,r);
    double a = 30, b=70;
    Point o = Point {r+a, 0};
    ellipse(o.x+XREF, -o.y+YREF, 0, 360, a,b);
    //ELLIPSE e = ELLIPSE {a,b,o};
    Point p1 = Point{XREF+r+a, YREF+b};
    Point p2 = Point{XREF+r+a, YREF-b};
    Point p3 = Point{XREF+r, YREF};
    Point p4 = Point{XREF+r+2*a, YREF};
    //e.plotFirstOrder(BLUE);
    int nctr = storePoints(stored2);

    ctr = 0;
    //locus ellipse
    Point orig = Point {0,0};
    ELLIPSE x = ELLIPSE {r+a, r+b, orig};
    x.plotFirstOrder(BLACK);

    plotEll(o, nctr, stored2, RED);
     double theta = (3.142857*10)/180.0;
    while(true)
    {
        rotate2(&o, theta);
        rotateSingle(&p1, -theta, Point{XREF, YREF});
        rotateSingle(&p2, -theta,Point{XREF, YREF});
        rotateSingle(&p3, -theta,Point{XREF, YREF});
        rotateSingle(&p4, -theta,Point{XREF, YREF});
        for(int j = 0; j<nctr; j++)
        {
            rotate2(&stored2[j], theta);
        }
        setcolor(WHITE);
        line(p1.x, p1.y, p2.x, p2.y);
        line(p3.x, p3.y, p4.x, p4.y);

        setcolor(YELLOW);
        ellipse(XREF,YREF,0,360,r,r);
        plotEll(o, nctr, stored2, WHITE);
        delay(100);
        cleardevice();
    }
    getch();
    closegraph();
    return 0;
}
