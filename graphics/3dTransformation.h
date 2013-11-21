#ifndef TRANS3D_H_INCLUDED
#define TRANS3D_H_INCLUDED
#include "line.h"
#include "math.h"
#define NUM_VERTICES 8
#define N 4
#define SW_X 160
#define SW_Y -120
typedef struct Point3D
{
    double x,y,z;
    void print()
    {
        printf("{%d, %d, %d} ", (int)x,(int)y,(int)z);
    }
};
void multiplyMatrix(double a[N][N], int r1, int c1 ,double b[N][NUM_VERTICES], int r2, int c2, double c[N][NUM_VERTICES]);
void translate(double matrix[N][NUM_VERTICES], int dx, int dy, int dz, double result[N][NUM_VERTICES]);
void scale(double matrix[N][NUM_VERTICES], double sx, double sy, double sz, double result[N][NUM_VERTICES]);
void rotateX(double matrix[N][NUM_VERTICES], double angleRad, double result[N][NUM_VERTICES]);
void rotateY(double matrix[N][NUM_VERTICES], double angleRad, double result[N][NUM_VERTICES]);
void rotateZ(double matrix[N][NUM_VERTICES], double angleRad, double result[N][NUM_VERTICES]);
void isometric(double matrix[N][NUM_VERTICES], double result[N][NUM_VERTICES]);

typedef struct Cube
{
    Point3D v[NUM_VERTICES];
    void plotFront(int color)
    {
        for(int i = 0; i<=3; i++)
        {
            plotLineFront(v[i], v[(i+1)%4], color);
            plotLineFront(v[i+4], v[(i+1)%4 + 4], color);
            plotLineFront(v[i], v[i+4], color);
        }
    }
    //xy
    void plotLineFront(Point3D p1, Point3D p2, int color)
    {
        Point p = {p1.x, p1.y};
        Point q = {p2.x, p2.y};
        Line l = {p, q};
        l.plotLineDDA(color);
    }

    void plotTop(int color)
    {
        for(int i = 0; i<=3; i++)
        {
            plotLineTop(v[i], v[(i+1)%4], color);
            plotLineTop(v[i+4], v[(i+1)%4 + 4], color);
            plotLineTop(v[i], v[i+4], color);
        }
    }
    //xz
    void plotLineTop(Point3D p1, Point3D p2, int color)
    {
        Point p = {p1.x, p1.z};
        Point q = {p2.x, p2.z};
        Line l = {p, q};
        l.plotLineDDA(color);
    }

    void plotSide(int color)
    {
        for(int i = 0; i<=3; i++)
        {
            plotLineSide(v[i], v[(i+1)%4], color);
            plotLineSide(v[i+4], v[(i+1)%4 + 4], color);
            plotLineSide(v[i], v[i+4], color);
        }
    }
    //yz
    void plotLineSide(Point3D p1, Point3D p2, int color)
    {
        Point p = {p1.y, p1.z};
        Point q = {p2.y, p2.z};
        Line l = {p, q};
        l.plotLineDDA(color);
    }

    void makePointMatrix(double pointMatrix[N][NUM_VERTICES])
    {
        for(int i = 0; i<NUM_VERTICES; i++)
        {
            pointMatrix[0][i] = v[i].x;
        }
        for(int i = 0; i<NUM_VERTICES; i++)
        {
            pointMatrix[1][i] = v[i].y;
        }
        for(int i = 0; i<NUM_VERTICES; i++)
        {
            pointMatrix[2][i] = v[i].z;
        }
        for(int i = 0; i<NUM_VERTICES; i++)
        {
            pointMatrix[3][i] = 1;
        }
    }

    void storePoints(double pointMatrix[N][NUM_VERTICES])
    {
        for(int i = 0; i<NUM_VERTICES; i++)
        {
            v[i].x = pointMatrix[0][i];
        }
        for(int i = 0; i<NUM_VERTICES; i++)
        {
            v[i].y = pointMatrix[1][i];
        }
        for(int i = 0; i<NUM_VERTICES; i++)
        {
            v[i].z = pointMatrix[2][i];
        }
    }
    void translateCube(int dx, int dy, int dz)
    {
        double pointMatrix[N][NUM_VERTICES];
        makePointMatrix(pointMatrix);
        double result[N][NUM_VERTICES];
        translate(pointMatrix, dx, dy, dz, result);
        storePoints(result);
    }

    void printCube()
    {
        for(int i = 0; i<NUM_VERTICES; i++)
        {
            printf("i = %d ", i);
            v[i].print();
            printf("\n");
        }
    }
    void scaleCube(double sx, double sy, double sz)
    {
        double pointMatrix[N][NUM_VERTICES];
        makePointMatrix(pointMatrix);
        double result[N][NUM_VERTICES];
        scale(pointMatrix, sx, sy, sz, result);
        storePoints(result);
    }
    void rotateCubeX(double angleRad)
    {
        double pointMatrix[N][NUM_VERTICES];
        makePointMatrix(pointMatrix);
        double result[N][NUM_VERTICES];
        rotateX(pointMatrix, angleRad, result);
        storePoints(result);
    }
    void rotateCubeY(double angleRad)
    {
        double pointMatrix[N][NUM_VERTICES];
        makePointMatrix(pointMatrix);
        double result[N][NUM_VERTICES];
        rotateY(pointMatrix, angleRad, result);
        storePoints(result);
    }
    void rotateCubeZ(double angleRad)
    {
        double pointMatrix[N][NUM_VERTICES];
        makePointMatrix(pointMatrix);
        double result[N][NUM_VERTICES];
        rotateZ(pointMatrix, angleRad, result);
        storePoints(result);
    }

    void plotIsometric(int color)
    {
        Point3D temp[NUM_VERTICES];
        for(int i = 0; i<NUM_VERTICES; i++)
        {
            temp[i] = v[i];
        }
        double pointMatrix[N][NUM_VERTICES];
        makePointMatrix(pointMatrix);
        double result[N][NUM_VERTICES];
        isometric(pointMatrix, result);
        storePoints(result);
        translateCube(SW_X, SW_Y, 0);
        plotFront(color);
        translateCube(-SW_X, -SW_Y, 0);
        //return to earlier points
        for(int i = 0; i<NUM_VERTICES; i++)
        {
            v[i] = temp[i];
        }

    }
};
void multiplyMatrix(double a[N][N], int r1, int c1 ,double b[N][NUM_VERTICES], int r2, int c2, double c[N][NUM_VERTICES])
{
    if(c1 != r2)
    {
        printf("Error in multiply matrix");
        return;
    }
    /*
    printf("Transformation matrix\n");
    for(int i = 0; i<N; i++)
    {
        for(int j = 0; j<N; j++)
        {
            printf("%d  ",(int) a[i][j]);
        }
        printf("\n");
    }
    printf("\n\nPoint Matrix\n");
    for(int i = 0; i<N; i++)
    {
        for(int j = 0; j<NUM_VERTICES; j++)
        {
            printf("%d  ", (int)b[i][j]);
        }
        printf("\n");
    }
    */
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
    /*
    printf("\n\nResultant matrix\n");
    for(int i = 0; i<N; i++)
    {
        for(int j = 0; j<NUM_VERTICES; j++)
        {
            printf("%d  ",(int) c[i][j]);
        }
        printf("\n");
    }
    */
}
void translate(double matrix[N][NUM_VERTICES], int dx, int dy, int dz, double result[N][NUM_VERTICES])
{
    //number of columns = number of points
    double transform[N][N] =
    {
        {1,0,0,dx},
        {0,1,0,dy},
        {0,0,1,dz},
        {0,0,0,1}
    };
    multiplyMatrix(transform, N, N, matrix, N, NUM_VERTICES,result);
}
void scale(double matrix[N][NUM_VERTICES], double sx, double sy, double sz, double result[N][NUM_VERTICES])
{
     double transform[N][N] = {
                         {sx,0,0,0},
                         {0,sy,0,0},
                         {0,0,sz,0},
                         {0,0,0,1}
                        };
    multiplyMatrix(transform, N, N, matrix, N, NUM_VERTICES,result);
}

void rotateX(double matrix[N][NUM_VERTICES], double angleRad, double result[N][NUM_VERTICES])
{
    double Cos = cos(angleRad);
    double Sin = sin(angleRad);
    double transform[N][N] = {
                         {1,0,0,0},
                         {0,Cos,-Sin,0},
                         {0,Sin,Cos,0},
                         {0,0,0,1}
                        };
    multiplyMatrix(transform, N, N, matrix, N, NUM_VERTICES,result);
}
void rotateY(double matrix[N][NUM_VERTICES], double angleRad, double result[N][NUM_VERTICES])
{
    double Cos = cos(angleRad);
    double Sin = sin(angleRad);
    double transform[N][N] = {
                         {Cos,0,Sin,0},
                         {0,1,0,0},
                         {-Sin,0,Cos,0},
                         {0,0,0,1}
                        };
    multiplyMatrix(transform, N, N, matrix, N, NUM_VERTICES,result);
}
void rotateZ(double matrix[N][NUM_VERTICES], double angleRad, double result[N][NUM_VERTICES])
{
    double Cos = cos(angleRad);
    double Sin = sin(angleRad);
    double transform[N][N] = {
                         {Cos,-Sin,0,0},
                         {Sin,Cos,0,0},
                         {0,0,1,0},
                         {0,0,0,1}
                        };
    multiplyMatrix(transform, N, N, matrix, N, NUM_VERTICES,result);
}
void isometric(double matrix[N][NUM_VERTICES], double result[N][NUM_VERTICES])
{
    double thetaY = 0.785;
    double thetaX = 0.6156;
    double tempResult[N][NUM_VERTICES];
    rotateY(matrix, thetaY, tempResult);
    rotateX(tempResult, thetaY, result);
}

void rotateXSingle(Point3D *p, double angleRad)
{
    double matrix[N][NUM_VERTICES] = {p->x, p->y, p->z, 1};
    double rslt[N][NUM_VERTICES];
    rotateX(matrix, angleRad, rslt);
    p->x = rslt[0][0];
    p->y = rslt[1][0];
    p->z = rslt[2][0];
}
#endif
