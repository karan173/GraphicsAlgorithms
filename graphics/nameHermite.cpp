#include "graphics.h"
#include "hermite.h"
#include "circle.h"
#include "fill.h"
int main()
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "");

    setbkcolor(WHITE);
    cleardevice();

    double x,y;
    x = -150, y = 150;
    drawK(x,y);

	x+=70, y-=5;
	drawR(x,y);
	x+=100, y+=5;
	drawN(x,y);

	x+=60;
	drawD(x,y);

	drawE(x,y);
	x+=70;
	drawP(x,y);
    x+=60;
	double endX = x+15;
	x = -150;
	double line[4][2] = {
                        x-30,y,
                        endX, y,
                        100,0,
                        100,0
                            };
    drawHermite(line, BLACK);

    x = -60, y = -10;
    drawS(x,y);
    drawSmallE(x+70,y);

    x += 150;
    drawH(x,y);
    endX = x+15;
    x = -120;
    double line2[4][2] = {
                        x,y,
                        endX, y,
                        100,0,
                        100,0
                            };
    drawHermite(line2, BLACK);
    Point p = {x+130, y+20};
    Circle c = {p,7};
    c.bressenPlot(BLACK);
    seedFill4(p, BLACK, BLACK);
	getch();
    closegraph();
    return 0;
}
