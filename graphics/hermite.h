#ifndef HERMITE_H_INCLUDED
#define HERMITE_H_INCLUDED
#include "3dTransformation.h"
#define N 4
double hermiteT[4][4] =
{
    {2,-2,1,1},
    {-3,3,-2,-1},
    {0,0,1,0},
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
void drawHermite(double p[4][2], int curveColor)
{
    double step = 0.001;
    double c[4][2];
    mult1(hermiteT, p, c);
    for(double t = 0; t<=1.0; t+=step)
    {
        double tMatrix[1][4] = {t*t*t, t*t, t, 1};
        double res[1][2];
        mult2(tMatrix, c, res);
        Point pp = {res[0][0], res[0][1]};
        pp.plotPoint(curveColor);
    }
}
/*
functions to draw alphabets in Hindi using hermite curves
*/
void drawK(double x, double y)
{
    double k1[4][2] = {
                    x,y,
                    x,y-100,
                    0,-10,
                    0,-10
                    };
    double k2[4][2] = {
                        x,y-50,
                        x,y-50,
                        -170, 300,
                        170,300
                        };

    double k3[4][2] = {
                    x,y-50,
                    x+40,y-100,
                    200,200,
                    0,-100
                        };

    drawHermite(k1, BLACK);
    drawHermite(k2, BLACK);
    drawHermite(k3, BLACK);
}
void drawR(double x, double y)
{
    double r1[4][2] = {
                    x,y,
                    x,y-50,
                    200,40,
                    -100,-20
                        };
    double r2[4][2] = {
                        x,y-50,
                        x+45, y-95,
                        100, -100,
                        100, -100
                        };

    drawHermite(r1, BLACK);
    drawHermite(r2, BLACK);
}

void drawN(double x, double y)
{
    double n1[4][2] = {
                        x,y,
                        x,y-100,
                        0,-100,
                        0, -100
                        };
    double n2[4][2] = {
                    x,y-50,
                    x-70, y-50,
                    -100,0,
                    -100, 0
                        } ;
    double n3[4][2] = {
                    x-70, y-50,
                    x-40, y-50,
                    100, -100,
                    100,100
                        };
    drawHermite(n1, BLACK);
    drawHermite(n2, BLACK);
    drawHermite(n3, BLACK);
}

void drawD(double x, double y)
{
    double d1[4][2] = {
                        x,y,
                        x,y-20,
                        0,-100,
                        0,-100
                        };
    double d2[4][2] = {
                        x,y-20,
                        x+10,y-65,
                        -150,0,
                        150,0
                        };
    double d3[4][2] = {
                    x+10,y-65,
                    x-10,y-100,
                    -100,-173,
                    -100,-173
                    };
    drawHermite(d1, BLACK);
    drawHermite(d2, BLACK);
    drawHermite(d3, BLACK);
}

void drawE(double x, double y)
{

    double e1[4][2] = {
                    x,y,
                    x+45,y,
                    0,100,
                    0,-100};
    double e2[4][2] = {
                    x+45,y,
                    x+45,y-100,
                    0,-100,
                    0,-100
                        };
    drawHermite(e1, BLACK);
    drawHermite(e2, BLACK);
}

void drawP(double x, double y)
{
    double p1[4][2] = {
                    x,y,
                    x+50, y,
                    0,-200,
                    0,200
                        };
    double p2[4][2] = {
                    x+50,y,
                    x+50, y-100,
                    0,-100,
                    0,-100
                        };
    drawHermite(p1, BLACK);
    drawHermite(p2, BLACK);
}

void drawS(double x, double y)
{
    double s1[4][2] = {
                    x,y,
                    x,y-50,
                    200,40,
                    -100,-20
                        };
    double s2[4][2] = {
                        x,y-50,
                        x+45, y-95,
                        100, -100,
                        100, -100
                        };
    double s3[4][2] = {
                        x, y-50,
                        x+70, y-50,
                        100,0,
                        100,0
                        };
    double s4[4][2] = {
                        x+70, y+5,
                        x+70, y-95,
                        0,-100,
                        0,-100
                        };
    drawHermite(s1, BLACK);
    drawHermite(s2, BLACK);
    drawHermite(s3, BLACK);
    drawHermite(s4, BLACK);
}
void drawSmallE(double x, double y)
{
    double e1[4][2] = {
                    x,y,
                    x-100,y,
                    -100,200,
                    0,-100};
    double e2[4][2] = {
                    x-100,y,
                    x-100,y-100,
                    0,-100,
                    0,-100
                        };
    drawHermite(e1, BLACK);
    drawHermite(e2, BLACK);
}

void drawH(double x, double y)
{
    double h1[4][2] = {
                        x,y,
                        x,y-20,
                        0,-100,
                        0,-100
                        };
    double h2[4][2] = {
                        x,y-20,
                        x,y-60,
                        -200,0,
                        200,0
                        };
    double h3[4][2] = {
                        x,y-60,
                        x,y-100,
                        -200,0,
                        200,0
                        };
    drawHermite(h1, BLACK);
    drawHermite(h2, BLACK);
    drawHermite(h3, BLACK);
}

void drawNewS(double x, double y)
{
    double s1[4][2] = {
                    x,y+50,
                    x,y,
                    200,40,
                    -100,-20
                        };
    double s2[4][2] = {
                        x,y,
                        x+45, y-45,
                        100, -100,
                        100, -100
                        };
    double s3[4][2] = {
                        x, y,
                        x+70, y,
                        100,-20,
                        100,20
                        };
    double s4[4][2] = {
                        x+70, y+55,
                        x+70, y-45,
                        0,-100,
                        0,-100
                        };
    double s5[4][2] = {
                        x-10, y+55,
                        x+80, y+55,
                        100,0,
                        100,0
                        };
    drawHermite(s1, BLACK);
    drawHermite(s2, BLACK);
    drawHermite(s3, BLACK);
    drawHermite(s4, BLACK);
    drawHermite(s5, BLACK);
}
#endif
