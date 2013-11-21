#include "3dTransformation.h"
#include "graphics.h"
#include "line.h"
#define NE_X -160
#define NE_Y 120
#define NW_X 160
#define NW_Y 120
#define SE_X -160
#define SE_Y -120
#define PI 3.142857
#define ESC 27
#define SPECIAL_KEY 224
Cube c;
int getKeyCode()
{
    int ch = getch();
    if(ch==0 || ch==SPECIAL_KEY)
    {
        return getch();
    }
    return ch;
}
double toRadian(double deg)
{
    return (PI*deg)/180.0;
}
void plotFront(int col)
{
    //xy
    c.translateCube(NE_X, NE_Y, 0);
    c.plotFront(col);
    c.translateCube(-NE_X, -NE_Y, 0);
}
void plotSide(int col)
{
    //yz
    c.translateCube(0, NW_X, NW_Y);
    c.plotSide(col);
    c.translateCube(0, -NW_X, -NW_Y);
}
void plotTop(int col)
{
    //xz
    c.translateCube(SE_X, 0, SE_Y);
    c.plotTop(col);
    c.translateCube(-SE_X, 0, -SE_Y);
}
void plotIsometric(int col)
{
    //on xy
    c.plotIsometric(col);
}
void plotCubes()
{
    cleardevice();
    drawAxis(BLACK);
    outtextxy(0,0,"Front view");
    outtextxy(XREF+1, 0, "Side view");
    outtextxy(XREF+1, YREF+1, "Isometric view");
    outtextxy(0, YREF+1, "Top view");
    plotFront(RED);
    plotSide(GREEN);
    plotTop(BLUE);
    plotIsometric(YELLOW);
}

int main()
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "");
    setbkcolor(WHITE);
    cleardevice();

    setcolor(BLACK);
    c.v[0] = {-40,40,40};
    c.v[1] = {-40,-40,40};
    c.v[2] = {40, -40, 40};
    c.v[3] = {40,40,40};
    c.v[4] = {-40,40,-40};
    c.v[5] = {-40,-40,-40};
    c.v[6] = {40,-40,-40};
    c.v[7] = {40,40,-40};
    plotCubes();
    int ch;
    while((ch = getKeyCode())!=ESC)
    {
        switch(ch)
        {
            case 'A' :
                c.rotateCubeX(toRadian(10));
                break;
            case 'W' :
                c.rotateCubeY(toRadian(10));
                break;
            case 'D' :
                c.rotateCubeZ(toRadian(10));
                break;
            case 'J' :
                c.rotateCubeX(toRadian(-10));
                break;
            case 'I' :
                c.rotateCubeY(toRadian(-10));
                break;
            case 'L' :
                c.rotateCubeZ(toRadian(-10));
                break;
            case 'X' :
                c.scaleCube(1.5,1.5,1.5);
                break;
            case 'C' :
                c.scaleCube(2/3.0, 2/3.0,2/3.0);
                break;
        }
        plotCubes();
    }
    getch();
    closegraph();
    return 0;
}
