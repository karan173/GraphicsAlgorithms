#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

typedef struct Rectangle Rect;
struct Rectangle
{
    Point min;
    Point max;
    void plotRect(int color)
    {
        Point a = {min.x, max.y};
        Point b = max;
        Point c = {max.x, min.y};
        Point d = min;
        Line l[] = {{a,b}, {b,c}, {c,d}, {d,a}};
        for(int i = 0; i<4; i++)
        {
            l[i].plotLineDDA(color);
        }
    }
    void print()
    {
        printf("Rectangle-\n");
        min.print();
        max.print();
    }
};

#endif // RECTANGLE_H_INCLUDED
