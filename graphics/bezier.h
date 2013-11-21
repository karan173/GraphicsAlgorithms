#include "point.h"
#include "circle.h"
#include "fill.h"
#define N 4
double bezierT[4][4] =
{
    {-1,3,-3,1},
    {3,-6,3,0},
    {-3,3,0,0},
    {1,0,0,0}
};

void mult1(double a[4][4], double b[4][2], double c[4][2])
{
    int r1 = 4, c2 = 2, r2 = 4;
    for(int i = 0; i<r1; i++)
    {
        for(int j = 0; j<c2; j++)
        {
            c[i][j] = 0;
            for(int k = 0; k<r2; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}
void mult2(double a[1][4], double b[4][2], double c[1][2])
{
    int r1 = 1, c2 = 2, r2 = 4;
    for(int i = 0; i<r1; i++)
    {
        for(int j = 0; j<c2; j++)
        {
            c[i][j] = 0;
            for(int k = 0; k<r2; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}
void drawBezier(double p[4][2], int curveColor, int endColor)
{
    double step = 0.0001;
    double c[4][2];
    mult1(bezierT, p, c);
    for(double t = 0; t<=1.0; t+=step)
    {
        double tMatrix[1][4] = {t*t*t, t*t, t, 1};
        double res[1][2];
        mult2(tMatrix, c, res);
        Point pp = {res[0][0], res[0][1]};
        //pp.print();
        pp.plotPoint(curveColor);
    }
    //color end points
    for(int i = 0; i<4; i++)
    {
        Point x = Point{p[i][0], p[i][1]};
        Circle c = Circle{x, 5};
        c.bressenPlot(endColor);
        seedFill4(x, endColor, endColor);
    }
}
