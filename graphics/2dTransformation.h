
#include "line.h"
#include "math.h"
#define NUM_VERTICES 16
#define N 3

void multiplyMatrix(double a[N][N], int r1, int c1 ,double b[N][NUM_VERTICES], int r2, int c2, double c[N][NUM_VERTICES]);
void translate(double matrix[N][NUM_VERTICES], int dx, int dy, int dz, double result[N][NUM_VERTICES]);
void scale(double matrix[N][NUM_VERTICES], double sx, double sy, double sz, double result[N][NUM_VERTICES]);
void rotate(double matrix[N][NUM_VERTICES], double angleRad, double result[N][NUM_VERTICES]);

void multiplyMatrix(double a[N][N], int r1, int c1 ,double b[N][NUM_VERTICES], int r2, int c2, double c[N][NUM_VERTICES])
{
    if(c1 != r2)
    {
        printf("Error in multiply matrix");
        return;
    }


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

void translate(double matrix[N][NUM_VERTICES], int dx, int dy, double result[N][NUM_VERTICES])
{
    //number of columns = number of points
    double transform[N][N] =
    {
        {1,0,dx},
        {0,1,dy},
        {0,0,1}
    };
    multiplyMatrix(transform, N, N, matrix, N, NUM_VERTICES,result);
}
void scale(double matrix[N][NUM_VERTICES], double sx, double sy, double result[N][NUM_VERTICES])
{
     double transform[N][N] = {
                         {sx,0,0},
                         {0,sy,0},
                         {0,0,1}
                        };
    multiplyMatrix(transform, N, N, matrix, N, NUM_VERTICES,result);
}

void rotate(double matrix[N][NUM_VERTICES], double angleRad, double result[N][NUM_VERTICES])
{
    double Cos = cos(angleRad);
    double Sin = sin(angleRad);
    double transform[N][N] = {
                         {Cos, -Sin, 0},
                         {Sin,Cos,0},
                         {0,0,1}
                        };
    multiplyMatrix(transform, N, N, matrix, N, NUM_VERTICES,result);
}
void multiplySingle(double a[N][N], int r1, int c1 ,double b[N][1], int r2, int c2, double c[N][1])
{
    if(c1 != r2)
    {
        printf("Error in multiply matrix");
        return;
    }



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
void rotateSingle(Point *p, double angleRad)
{
    double Cos = cos(angleRad);
    double Sin = sin(angleRad);

    double transform[N][N] = {
                         {Cos, -Sin, 0},
                         {Sin,Cos,0},
                         {0,0,1}
                        };

    double matrix[3][1] = {p->x, p->y, 1};
    double rslt[3][1];
    multiplySingle(transform, N, N, matrix, N, 1, rslt);

    p->x = rslt[0][0];
    p->y = rslt[1][0];
}

void translateSingle(Point *p,int dx, int dy)
{
    double transform[N][N] =
    {
        {1,0,dx},
        {0,1,dy},
        {0,0,1}
    };
    double matrix[3][1] = {p->x, p->y, 1};
    double rslt[3][1];
    multiplySingle(transform, N, N, matrix, N, 1, rslt);
    p->x = rslt[0][0];
    p->y = rslt[1][0];
}

void scaleSingle(Point *p,double sx,double sy)
{
    double transform[N][N] = {
                         {sx,0,0},
                         {0,sy,0},
                         {0,0,1}
                        };
    double matrix[3][1] = {p->x, p->y, 1};
    double rslt[3][1];
    multiplySingle(transform, N, N, matrix, N, 1, rslt);
    p->x = rslt[0][0];
    p->y = rslt[1][0];
}

void shearX(Point *p, int sx, int yref)
{
    double transform[N][N] =
    {
        {1,sx,-sx*yref},
        {0,1,0},
        {0,0,1}
    };
    double matrix[3][1] = {p->x, p->y, 1};
    double rslt[3][1];
    multiplySingle(transform, N, N, matrix, N, 1, rslt);
    p->x = rslt[0][0];
    p->y = rslt[1][0];
}

void shearY(Point *p, int sy, int xref)
{
    double transform[N][N] =
    {
        {1,0,0},
        {sy,1,-sy*xref},
        {0,0,1}
    };
    double matrix[3][1] = {p->x, p->y, 1};
    double rslt[3][1];
    multiplySingle(transform, N, N, matrix, N, 1, rslt);
    p->x = rslt[0][0];
    p->y = rslt[1][0];
}
