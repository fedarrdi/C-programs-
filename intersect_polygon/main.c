#include <stdio.h>
#include <math.h>
#include<stdlib.h>

struct point { float x, y; };
struct section { struct point start, end; };
enum bool{ false,true };

float get_area(struct point a, struct point b, struct point c)
{
    float d = (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2;
    return (d < 0) ? (-d) : (d);
}

float get_area_of_polygon(const struct point* polygon, struct point p, unsigned len, int start)
{
    float area = 0;
    int minus = (start) ? 2 : 1;
    for (int i = start; i < len - minus; i++)
        area += get_area(p, polygon[i], polygon[i + 1]);
    return area;
}

enum bool is_point_in_polygon(const struct point* polygon, struct point a, unsigned len)
{
    return (get_area_of_polygon(polygon, polygon[0], len, 1) >= get_area_of_polygon(polygon, a, len, 0)) ? true : false;
}

enum bool findIntersection(struct point* result, struct section a, struct section b)
{
    float x1 = a.start.x, y1 = a.start.y, x2 = a.end.x, y2 = a.end.y, x3 = b.start.x, y3 = b.start.y, x4 = b.end.x, y4 = b.end.y;

    float a1 = y2 - y1;
    float b1 = x1 - x2;
    float c1 = a1 * x1 + b1 * y1;

    float a2 = y4 - y3;
    float b2 = x3 - x4;
    float c2 = a2 * x3 + b2 * y3;

    float d = a1 * b2 - a2 * b1;

    if (d == 0) return false;

    float x = (b2 * c1 - b1 * c2) / d;
    float y = (a1 * c2 - a2 * c1) / d;
    enum bool online1 =
            ((fmin(x1, x2) < x || fmin(x1, x2) == x) &&
             (fmax(x1, x2) > x || fmax(x1, x2) == x) &&
             (fmin(y1, y2) < y || fmin(y1, y2) == y) &&
             (fmax(y1, y2) > y || fmax(y1, y2) == y));
    enum bool online2 =
            ((fmin(x3, x4) < x || fmin(x3, x4) == x) &&
             (fmax(x3, x4) > x || fmax(x3, x4) == x) &&
             (fmin(y3, y4) < y || fmin(y3, y4) == y) &&
             (fmax(y3, y4) > y || fmax(y3, y4) == y));
    if (online1 && online2)
    {
        result->x = x, result->y = y;
        return true;
    }

    return false;
}

unsigned get_length(const struct point* polygon)
{
    struct point p1 = *polygon;
    unsigned len = 2;
    polygon++;
    while (p1.x != polygon->x || p1.y != polygon->y)
        len++, polygon++;

    return len;
}

enum bool intersect_polygons(struct point* result, const struct point* polygon1, const struct point* polygon2)
{
    enum bool check = false;
    unsigned l1 = get_length(polygon1), l2 = get_length(polygon2), l3 = 0;

    for (int i = 0; i < l1 - 1; i++)
    {
        if (is_point_in_polygon(polygon2, polygon1[i], l2))
        {
            check = true;
            result[l3++] = polygon1[i];

        }
        int index1 = (i + 1 == l1 - 1) ? 1 : i + 1;
        struct section a = {polygon1[i], polygon1[index1]};

        for (int j = 0; j < l2 - 1; j++)
        {
            struct section b = {polygon2[j], polygon2[j + 1]};

            if (findIntersection(&result[l3], a, b))
                l3++;
        }
    }

    for (int i = 0; i < l2 - 1; i++)
        if (is_point_in_polygon(polygon1, polygon2[i], l1))
        {
            result[l3] = polygon2[i];
            l3++;
        }


    result[l3++] = result[0];
    for(int i = 0;i < l3;i++)
        printf("%d, %d\n", result[i].x, result[i].y);
    return check;
}

int main() {
    struct point polygon1[9] = { {8, 4}, {10, 6}, {10, 8}, {8, 10}, {6, 10}, {4, 8},{4, 6}, {6, 4}, {8, 4} };
    struct point polygon2[6] = { {6, 2}, {8, 6}, {6, 8}, {0, 6}, {2, 4}, {6, 2} };
    struct point result[15];
    intersect_polygons(result, polygon1, polygon2);
    return 0;
}
