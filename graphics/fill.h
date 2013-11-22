#ifndef FILL_H_INCLUDED
#define FILL_H_INCLUDED
#include<graphics.h>
#define MAXSTACK 20000
int dx8[] = {-1,0,1,-1,1,-1,0,1};
int dy8[] = {-1,-1,-1,0,0,1,1,1};
int dx4[] = {-1, 0, 1, 0};
int dy4[] = {0,-1,0,1};
void seedFill8(Point p, int fillColor, int boundaryColor)
{
    int curColor = p.getColor();
    if(curColor!=fillColor && curColor!=boundaryColor)
    {
        p.plotPoint(fillColor);
        for(int k = 0; k<8; k++)
        {
            Point q = {p.x+dx8[k], p.y+dy8[k]};
            seedFill8(q, fillColor, boundaryColor);
        }
    }
}
Point stack[MAXSTACK];
int stackCtr;

void seedFill4(Point p, int fillColor, int boundaryColor)
{
    stackCtr = 0;
    stack[stackCtr++] = p;
    p.plotPoint(fillColor);
    while(stackCtr)
    {
        p = stack[--stackCtr];
        for(int k = 0; k<4; k++)
        {
            Point q = {p.x+dx4[k], p.y+dy4[k]};
            if(q.getColor()!=fillColor && q.getColor()!=boundaryColor)
            {
                q.plotPoint(fillColor);
                stack[stackCtr++] = q;
            }
        }
    }
}

#endif // FILL_H_INCLUDED
