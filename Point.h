//
// Created by fedar on 12/25/2022.
//

#ifndef POOL_POINT_H
#define POOL_POINT_H

#include<math.h>
#include<iostream>

struct Point
{
    float x, y;

    Point operator+(const Point &p) const {
        return {x+p.x, y+p.y};
    }
    Point operator-(const Point &p) const {
        return {x-p.x, y-p.y};
    }
    Point operator*(float c) const {
        return {c*x, c*y};
    }
    Point operator/(float c) const {
        return {x/c, y/c};
    }
    float operator*(const Point &p) const {
        return x*p.x + y*p.y;
    }
    void print()
    {
        std::cout << "x: " << x << " y: "  << y << std::endl;
    }

    float get_dist()
    {
        return sqrt(x*x+y*y);
    }

    float get_dist(Point other)
    {
        float rx = x - other.get_x(), ry = y - other.get_y();
        return sqrt(rx*rx+ry*ry);
    }

    float get_x() const { return x; }
    float get_y() const { return y; }
};

#endif //POOL_POINT_H
