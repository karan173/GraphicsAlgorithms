#ifndef CLIPPING_H_INCLUDED
#define CLIPPING_H_INCLUDED

#include "point.h"
#include "line.h"
#include "rectangle.h"
#include "polygon.h"
#define L 0x1
#define B 0x2
#define R 0x4
#define T 0x8
#define Max(a, b) ((a>b)?a:b)
#define Min(a, b) ((a>b)?b:a)
int genCode(Point *p, Rect *r)
{
    int code  = 0;
    if( (p->x) < (r->min.x))
    {
        code |= L;
    }
    else if( (p->x) > (r->max.x))
    {
        code |= R;
    }
    if((p->y) < (r->min.y))
    {
        code |= B;
    }
    else if((p->y) > (r->max.y))
    {
        code |= T;
    }
    return code;
}
/*
check extensively
*/
void clipMidPointSubdivision(Rect *r, Line *l, int color)
{
    int code1 = genCode(&(l->p1), r);
    int code2 = genCode(&(l->p2), r);
    //l->plotLineDDA(WHITE);
    if((code1|code2) == 0) //line inside rectangle
    {
        l->plotLineDDA(color);
        return;
    }
    if(code1&code2) //line outside rectangle
    {
        return;
    }
    //partially inside
    Point mid = midPoint(l);
    Line l1 = {l->p1, mid};
    Line l2 = {mid, l->p2};
    if(mid.x != l->p2.x || mid.y != l->p2.y) //if l1!=current line
        clipMidPointSubdivision(r, &l1, color);
    if(mid.x != l->p1.x || mid.y != l->p1.y) //if l2!=current line
        clipMidPointSubdivision(r, &l2, color);
}


void cohenSutherland(Rect *rr, Line l, int color)
{
    Rect r = *rr;
    while(1)
    {
        int code1 = genCode(&(l.p1), rr);
        int code2 = genCode(&(l.p2), rr);
        if((code1|code2) == 0)
        {
            l.plotLineDDA(color);
            return;
        }
        if(code1&code2) //on same side of a region, hence outside
        {
            return;
        }
        if(!code1) //pt1 inside rectangle, swap with pt 2
        {
            Point t = l.p1;  //
            l.p1 = l.p2;
            l.p2 = t;
            code1 = code2;
        }
        //find intersection pts.
        //only do 1 intersection pt inside 1 iteration
        if(code1 & L)
        {
            l.p1.y = l.p1.y+ ((l.p2.y-l.p1.y)*(r.min.x-l.p1.x))/(l.p2.x-l.p1.x);
            l.p1.x = r.min.x;
        }
        else if(code1 & R)
        {
            l.p1.y = l.p1.y+ ((l.p2.y-l.p1.y)*(r.max.x-l.p1.x))/(l.p2.x-l.p1.x);
            l.p1.x = r.max.x;
        }
        else if(code1 & T)
        {
            l.p1.x = l.p1.x + ((l.p2.x-l.p1.x)*(r.max.y-l.p1.y))/(l.p2.y - l.p1.y);
            l.p1.y = r.max.y;
        }
        else if(code1 & B)
        {
            l.p1.x = l.p1.x + ((l.p2.x-l.p1.x)*(r.min.y-l.p1.y))/(l.p2.y - l.p1.y);
            l.p1.y = r.min.y;
        }
    }
}

/* sutherland - hodgeman polygon clipping */
typedef enum
{
    Top,Bottom, Left, Right
} Edge;
#define N_EDGE 4
#define INSIDE 1

int getStatus(Point p, Rect *r, Edge e)
{
    switch(e)
    {
    case Left :
        if(p.x < r->min.x)
            return !INSIDE;
        break;
    case Right :
        if(p.x > r->max.x)
            return !INSIDE;
        break;
    case Top :
        if(p.y > r->max.y)
            return !INSIDE;
        break;
    case Bottom :
        if(p.y < r->min.y)
            return !INSIDE;
        break;
    }
    return INSIDE;
}
Point getIntersection(Line l, Rect *rr, Edge e)
{
    double x,y;
    Rect r = *rr;
    switch(e)
    {
    case Left :
        y = l.p1.y + ((l.p2.y-l.p1.y)*(r.min.x-l.p1.x))/(l.p2.x-l.p1.x);
        x = r.min.x;
        break;
    case Right :
        y = l.p1.y + ((l.p2.y-l.p1.y)*(r.max.x-l.p1.x))/(l.p2.x-l.p1.x);
        x = r.max.x;
        break;
    case Top :
        x = l.p1.x + ((l.p2.x-l.p1.x)*(r.max.y-l.p1.y))/(l.p2.y - l.p1.y);
        y = r.max.y;
        break;
    case Bottom :
        x = l.p1.x + ((l.p2.x-l.p1.x)*(r.min.y-l.p1.y))/(l.p2.y - l.p1.y);
        y = r.min.y;
        break;
    }
    return Point {x,y};
}
/*
this returns clipped polygon
Doesn't work perfectly for Concave polygons - as expected
extra lines are displayed
*/
Poly* sutherlandHodgeman(Poly *head, Rect *r)
{
    for(int ii =  0; ii<N_EDGE; ii++)
    {
        Edge i = (Edge) ii;
        Poly *op = NULL;
        Poly *x;
        Point first;
        for(Poly *v = head; v && v->next ; v = v->next)
        {
            int code1 = getStatus(v->p, r, i);
            int code2 = getStatus(v->next->p, r, i);
            if(code1 != INSIDE && code2 != INSIDE)  //o o
            {
            }
            else if(code1 == INSIDE && code2 == INSIDE) //i i add V2
            {
                if(!op)
                {
                    first = v->next->p;
                }
                x = (Poly *) malloc (sizeof(Poly));
                *x = {v->next->p, op};
                op = x;
            }
            else if(code1 == INSIDE && code2!=INSIDE) //i o , add intersection point
            {

                Point y = getIntersection(Line {v->p, v->next->p}, r, i);
                if(!op)
                {
                    first = y;
                }
                x = (Poly *) malloc (sizeof(Poly));
                *x = {y, op};
                op = x;
            }
            else // o i add intersection and then v2
            {
                Point y = getIntersection(Line {v->p, v->next->p}, r, i);
                if(!op)
                {
                    first = y;
                }
                x = (Poly *) malloc (sizeof(Poly));
                *x = {y, op};
                op = x;

                x = (Poly *) malloc (sizeof(Poly));
                *x = {v->next->p, op};
                op = x;
            }
        }
        //finally add first point
        x = (Poly *) malloc (sizeof(Poly));
        *x = {first, op};
        op = x;
        head = op;
        /*
        MEMORY LEAK
        head not deleted
        */
    }
    return head;
}

/*
Liang barsky
*/
void liangBarsky(Rect *r, Line *ll, int color)
{
    Rect rr = *r;
    Line l = *ll;
    int delX = l.p2.x - l.p1.x;
    int delY = l.p2.y - l.p1.y;
    int p[] = {
                -delX, //L
                delX, //R
                -delY, //B
                delY  //T
                };
    int q[] = {
                l.p1.x - rr.min.x,
                rr.max.x - l.p1.x,
                l.p1.y - rr.min.y,
                rr.max.y - l.p1.y
              };
    double u1 = 0;
    double u2 = 1;
    for(int i = 0; i<4; i++)
    {
        if(p[i]==0) // || to boundary
        {
            if(q[i]<0) //rejected
            {
                return;
            }
            continue; //no intersection with current edge since parallel
        }
        double u = ((double)q[i])/p[i];
        if(p[i]<0) //outside to inside
        {
            u1 = Max(u1, u);
        }
        else if(p[i]>0) //inside to outside
        {
            u2 = Min(u2, u);
        }
    }
    if(u1>u2) //rejected
    {
        return;
    }
    double x1 = l.p1.x + delX * u1;
    double y1 = l.p1.y + delY * u1;
    double x2 = l.p1.x + delX * u2;
    double y2 = l.p1.y + delY * u2;
    Line lClip = {Point{x1,y1}, Point{x2,y2}};
    lClip.plotLineDDA(color);
}
/*
Liang barsky end
*/


/*
Cyrus Beck
*/

double dotProduct(Point p1, Point p2)
{
    return p1.x*p2.x + p1.y*p2.y;
}
//z is a point on polygon other than on line l
/*
had a lot of trouble in this method - see this carefully
*/
Point getInsideNormal(Line l, Point z)
{
    double delX = l.p2.x - l.p1.x;
    double delY = l.p2.y - l.p1.y;
    Point n = {-delY, delX};
    Point v = {z.x-l.p1.x, z.y-l.p1.y};
    double dot = dotProduct(v,n);
    if(dot==0)
    {
        printf("Error - 3 collinear points along polygon\n");
        delay(2000);
        exit(0);
    }
    if(dot < 0) //outside normal
    {
        n.x*=-1;
        n.y*=-1;
    }
    return n;
}

/*
only for convex polygon
*/
void cyrusBeck(Poly *poly, Line *ll, int color)
{
    Line l = *ll;
    int delX = l.p2.x - l.p1.x;
    int delY = l.p2.y - l.p1.y;
    //vector D = Direction vector
    Point D = {delX, delY};

    //iterate over edges of polygon
    Point boundaryPoint = poly->next->next->p;
    double tEnter = 0;
    double tLeave = 1;
    while(1)
    {
        if(poly->next == NULL) //no more edges
        {
            break;
        }
        Point p = poly->p;
        p.print();
        poly = poly->next;
        Point q = poly->p;
        Line line = Line{p,q};
        Point n = getInsideNormal(line, boundaryPoint);
        //f = p1
        Point w = {l.p1.x-p.x, l.p1.y - p.y};
        double num = dotProduct(w, n);
        double den = dotProduct(D, n);
        if(den == 0) //line and edge are parallel
        {
            if(num < 0) //w.n<0  -> point/line outside coz P(t) outside polygon
            {
                return;
            }
            else
            {
                continue;
            }
        }

        double t = -num/den;
        if(den > 0) //outside to inside case
        {
            tEnter = Max(tEnter, t);
        }
        else //den < 0, inside to outside case
        {
            tLeave = Min(tLeave, t);
        }
        boundaryPoint = p;
    }
    if(tEnter > tLeave)
    {
        return;
    }
    double x1 = l.p1.x + delX * tEnter;
    double y1 = l.p1.y + delY * tEnter;
    double x2 = l.p1.x + delX * tLeave;
    double y2 = l.p1.y + delY * tLeave;
    Line lClip = {Point{x1,y1}, Point{x2,y2}};
    lClip.plotLineDDA(color);
}
/*
Cyrus Beck end
*/

#endif // CLIPPING_H_INCLUDED
