#include<iostream>
#include<cmath>
#include <utility>

using namespace std;

#define PI 3.14

class Point
{
    int x, y;

public:
    Point(int x, int y) : x(x), y(y) { }

    int get_x() const
    {
        return x;
    }

    int get_y() const
    {
        return y;
    }
};

class Section
{
    Point a, b;

public:
    Section(const Point &a, const Point &b) : a(a), b(b) { }

    double dist()
    {
        double rx = a.get_x() - b.get_x();
        double ry = a.get_y() - b.get_y();
        return sqrt(rx*rx + ry*ry);
    }
};

class Figure
{

    Point center;
    string type;

public:

    Figure(const Point &center, string type) : center(center), type(std::move(type)) { }

    void print_figure_type()
    {
        cout << "this figure is " << type << endl;
    }

    double dist_from(const Figure& other)
    {
        Section sec = Section(center, other.center);
        return sec.dist();
    }

    virtual void print_information()
    {
        cout << "None" << endl;
    }
};

class Circle : public Figure
{
    unsigned r;

public:
    Circle(const Point &center, string type, unsigned r) : Figure(center, std::move(type)), r(r) { }

    void print_information()
    {
        cout << "r = " << r << " S = " << 2 * PI * r << endl;
    }

};

class Square : public Figure
{
    unsigned length;
public:
    Square(const Point &center, string type, unsigned length) : Figure(center, std::move(type)), length(length) { }

    void print_information()
    {
        cout << "length of side = " << length << " S = " << length * length << endl;
    }
};


int main()
{
    Point center_a = Point(0, 0);
    Square a = Square(center_a, "square", 3);

    a.print_information();
    a.print_figure_type();

    Point center_b = Point(1, 1);
    Circle b = Circle(center_b, "circle", 3);

    b.print_information();
    b.print_figure_type();

    cout << b.dist_from(a) << endl;

    return 0;
}
