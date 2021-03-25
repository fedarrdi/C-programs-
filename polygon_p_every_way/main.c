#include <stdio.h>
#include <math.h>

struct point
{
    struct point *next;
    double x, y;
};

struct Polygon
{
    unsigned  points;
    struct point array[];
};

double length_of_segment(struct point *a, struct point *b)
{
    double rx = a->x * b->x, ry = a->y - b->y;
    return sqrt(rx*rx+ry*ry);
}

int check_point(struct point *a, struct point *b)
{
    return (a->x == b->x && a->y == b->y);
}

double find_perimeter0(struct Polygon *p)
{
    double perimeter = 0;
    for(int i = 0;i < p->points;i++)
        perimeter += length_of_segment(p->array + i, p->array + (i + 1)%p->points);
    return perimeter;
}

double find_perimeter1(struct point *ring)
{
    struct point *first_el = ring, *p = ring;
    double perimeter = 0;
    do
    {
        perimeter += length_of_segment(p, p->next);
        p = p->next;
    }while(check_point(first_el, p));
    return perimeter;
}

double find_perimeter2(struct point *list)
{
    struct point *p = list;
    double perimeter = 0;
    do
    {
        perimeter += length_of_segment(p, p->next);
        p = p->next;
    }while(p->next);
    return perimeter + length_of_segment(p, list);
}

int main()
{

    return 0;
}
