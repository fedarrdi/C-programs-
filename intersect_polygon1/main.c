#include<math.h>

struct point {  float x, y; };
struct section {  struct point start, end; };
enum bool { false, true };

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
    if (online1 && online2) {
        result->x = x, result->y = y;
        return true;
    }

    return false;
}


struct rectangle {  struct point a, b; };

unsigned crop(struct section *array, unsigned length, struct rectangle within)
{
    struct point c = {within.a.x, within.b.y} , d = {within.b.x, within.a.y};
    struct section s[4] = {{within.a, c}, {within.a, d}, {within.b, c}, {within.b, d}};
    struct section *wr = array, *src = array;

    while(--length)
    {
        for (int j = 0; j < 4; j++)
        {
            if (findIntersection(&wr->start, s[j], *src)) continue;

            if (findIntersection(&wr->end, s[j], *src)) wr++;
        }
        src++;
    }
    return src - wr;
}
int main() {
    struct rectangle rect = { {0,2},{4,0} };
    struct section a[] = {
            {{-3,4},{0,5}} ,
            {{-1,0},{2,3}} ,
            {{3,1},{2,3}},
            {{1,-1},{2,1}},
            {{2,1},{3,1}},
            {{5,2},{3,1}},
    };
    unsigned b = crop(a, 6, rect);

    return 0;
}
