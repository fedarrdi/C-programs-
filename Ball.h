//
// Created by fedar on 12/25/2022.
//

#ifndef POOL_BALL_H
#define POOL_BALL_H

#include"Point.h"

class Ball
{
private:
    Point position;
    float d;

public:

    Ball(Point position, float d)
    {
        this->position = position;
        this->d = d;
    }

    Ball() {}

    Point get_position() const { return position; }
    float get_r() const { return d / 2;}

    void set_position(const Point &position) { this->position = position; }

    bool is_ball_on_table(Point a, Point b, Point c, Point d)
    {
        return true;

    }

};


#endif //POOL_BALL_H
