#include<graphics.h>
#include "2dTransformation.h"
#include "line.h"
#define PI 3.142857
#define ESC 27
#define SPECIAL_KEY 224
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
int main()
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "");
    setbkcolor(WHITE);

    Point p[4] =
    {
        Point{0,0},
        Point{100,0},
        Point{100,100},
        Point{0,100}
    };
    int ch;
    cleardevice();
    drawAxis(BLACK);
    for(int i = 0; i<4; i++)
    {
        Line l = {p[i], p[(i+1)%4]};
        l.plotLineDDA(RED);
    }
    while((ch = getKeyCode())!=ESC)
    {
        switch(ch)
        {
        case 'A' :
            for(int i = 0; i<4; i++)
            {
                rotateSingle(&p[i], toRadian(10));
            }
            break;
        case 'W' :
            for(int i = 0; i<4; i++)
            {
                translateSingle(&p[i], 10,10);
            }
            break;
        case 'D' :
            for(int i = 0; i<4; i++)
            {
                scaleSingle(&p[i], 1.5, 1.5);
            }
            break;
        }
        cleardevice();
        drawAxis(BLACK);
        for(int i = 0; i<4; i++)
        {
            Line l = {p[i], p[(i+1)%4]};
            l.plotLineDDA(RED);
        }
    }
    return 0;
}
