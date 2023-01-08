//
// Created by fedar on 12/25/2022.
//

#ifndef POOL_TABLE_H
#define POOL_TABLE_H

#include<iostream>
#include "Point.h"
#include "Ball.h"
#include <limits>

using namespace std;

const double eps = 0.000001;

class Table
{

private:
    Ball ball;
    Point a, b, c, d;
    Point right_dir, up_dir;
    float lowc, highc, leftc, rightc;
    bool is_table_valid = true;

public:
    Table(Point start, int width, int height, Ball ball)
    {
        a = start;
        b = {start.get_x() + (float)width, start.get_y()};
        c = {start.get_x() + (float)width, start.get_y() + (float)height};
        d = {start.get_x() + (float)height, start.get_y()};

        if(a.get_dist(b) != b.get_dist(c) / 2 && a.get_dist(b) != b.get_dist(c) * 2)
        {
            std::cout << "Not valid points" << std::endl;
            is_table_valid = false;
        }

        if(!ball.is_ball_on_table(a, b, c, d))
        {
            std::cout << "Ball not on the table" << std::endl;
            is_table_valid = false;
        }

        this->ball = ball;

        ///calculate a vector from a to b with length of one
        right_dir = b-a;
        right_dir = right_dir / right_dir.get_dist();

        ///calculate a vector from a to d with length of one
        up_dir    = d-a;
        up_dir    = up_dir / up_dir.get_dist();

        /// we don't calculate left_dir and down_dir because they are the opposite of right_dir and up_dir

        ///constants we use for calculations
        lowc   = a*up_dir    + ball.get_r();
        highc  = d*up_dir    - ball.get_r();
        leftc  = a*right_dir + ball.get_r();
        rightc = b*right_dir - ball.get_r();
    }

    Table(Point a, Point b, Point c, Point d, Ball ball)
    {
        if(a.get_dist(b) != b.get_dist(c) / 2 && a.get_dist(b) != b.get_dist(c) * 2)
        {
            std::cout << "Not valid points" << std::endl;
            is_table_valid = false;
        }

        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;

        if(!ball.is_ball_on_table(a, b, c, d))
        {
            std::cout << "Ball not on the table" << std::endl;
            is_table_valid = false;
        }

        this->ball = ball;

        right_dir = b-a;
        right_dir = right_dir / right_dir.get_dist();
        up_dir    = d-a;
        up_dir    = up_dir / up_dir.get_dist();

        lowc   = a*up_dir    + ball.get_r();
        highc  = d*up_dir    - ball.get_r();
        leftc  = a*right_dir + ball.get_r();
        rightc = b*right_dir - ball.get_r();
    }

    void change_table(int width, int height)
    {
        if(width != 2 * height || width != height / 2)
        {
            std::cout << "Invalid table dimentions" << std::endl;
            return;
        }

        b = {a.get_x() + width, a.get_y()};
        c = {a.get_x() + width, a.get_y() + height};
        d = {a.get_x(), a.get_y() + height};

        right_dir = b-a;
        right_dir = right_dir / right_dir.get_dist();
        up_dir    = d-a;
        up_dir    = up_dir / up_dir.get_dist();

        lowc   = a*up_dir    + ball.get_r();
        highc  = d*up_dir    - ball.get_r();
        leftc  = a*right_dir + ball.get_r();
        rightc = b*right_dir - ball.get_r();

    }

    void change_table( Point start, int width, int height)
    {
        if(width != 2 * height || width != height / 2)
        {
            std::cout << "Invalid table dimentions" << std::endl;
            return;
        }

        a = start;
        b = {a.get_x() + width, a.get_y()};
        c = {a.get_x() + width, a.get_y() + height};
        d = {a.get_x(), a.get_y() + height};

        right_dir = b-a;
        right_dir = right_dir / right_dir.get_dist();
        up_dir    = d-a;
        up_dir    = up_dir / up_dir.get_dist();

        lowc   = a*up_dir    + ball.get_r();
        highc  = d*up_dir    - ball.get_r();
        leftc  = a*right_dir + ball.get_r();
        rightc = b*right_dir - ball.get_r();
    }

    void change_table(Point a, Point b, Point c, Point d)
    {
        if(a.get_dist(b) != b.get_dist(c) / 2 && a.get_dist(b) != b.get_dist(c) * 2)
        {
            std::cout << "Not valid points" << std::endl;
            is_table_valid = false;
        }
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;

        right_dir = b-a;
        right_dir = right_dir / right_dir.get_dist();
        up_dir    = d-a;
        up_dir    = up_dir / up_dir.get_dist();

        lowc   = a*up_dir    + ball.get_r();
        highc  = d*up_dir    - ball.get_r();
        leftc  = a*right_dir + ball.get_r();
        rightc = b*right_dir - ball.get_r();
    }

    void change_ball(Ball ball)
    {
        if(!ball.is_ball_on_table(a, b, c, d))
        {
            std::cout << "Ball not on the table" << std::endl;
            return;
        }

        this->ball = ball;

        lowc   = a*up_dir    + ball.get_r();
        highc  = d*up_dir    - ball.get_r();
        leftc  = a*right_dir + ball.get_r();
        rightc = b*right_dir - ball.get_r();
    }

    Ball get_ball() const { return ball; }



    /**
      get_power functions - in every function the power is the unknown
            the function returns the power needed for the ball to collide with corresponding wall of the pool table
     */

    float get_low_power(Point direction) const
    {
        if (abs(up_dir*direction) < eps) return std::numeric_limits<float>::infinity();
        return (lowc - up_dir*ball.get_position())/(up_dir*direction);
    }
    float get_high_power(Point direction) const
    {
        if (abs(up_dir*direction) < eps) return std::numeric_limits<float>::infinity();
        return (highc - up_dir*ball.get_position())/(up_dir*direction);
    }
    float get_left_power(Point direction) const
    {
        if (abs(right_dir*direction) < eps) return std::numeric_limits<float>::infinity();
        return (leftc - right_dir*ball.get_position())/(right_dir*direction);
    }

    float get_right_power(Point direction) const
    {
        if (abs(right_dir*direction) < eps) return std::numeric_limits<float>::infinity();
        return (rightc - right_dir*ball.get_position())/(right_dir*direction);
    }

    void strike(Point destination, float power)
    {
        Point direction = destination - ball.get_position();

        /**
         * on every iteration of the while from power is substarcated the current power
         */

        while (power > eps)
        {

            /// array with the powers needed for the ball to hit each wall of the table

            float pows[4] =
            {
                    get_low_power(direction),
                    get_high_power(direction),
                    get_left_power(direction),
                    get_right_power(direction)
            };

            /// we take the smallest non negative power and we apply it

            int p = -1;
            for (int i=0; i<4; ++i)
                if (pows[i] > eps && (p == -1 || pows[i] < pows[p]))
                    p = i;

            /// we check if the remained power is smaller from the power needed to hit the wall we only change the position of the ball and don't change the direction
            if (pows[p] > power - eps)
            {
                ball.set_position(ball.get_position() + direction * power);
                return;/// because the power is not enough for a hit we return because the ball will no longer move
            }

            ball.set_position(ball.get_position() + direction * pows[p]);

            if (p == 0 || p == 1) /// direction change for up and down wall
                direction = direction - up_dir*2*(direction*up_dir);

             else///direction chage for left and right wall
                direction = direction - right_dir*2*(direction*right_dir);

            power -= pows[p];
        }
    }
};

#endif //POOL_TABLE_H
