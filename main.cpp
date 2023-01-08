#include<iostream>
#include "Table.h"

using namespace std;

int main()
{
     {
     	Ball b(Point{280, 70}, 0);
     	Table t(Point{0, 0}, Point{320, 0}, Point{320, 160}, Point{0, 160}, b);

    	t.strike(Point{230,110}, 2);

     	t.get_ball().get_position().print();
     }
     {
     	Ball b(Point{300, 60}, 0);
     	Table t(Point{0, 0}, Point{320, 0}, Point{320, 160}, Point{0, 160}, b);

    	t.strike(Point{250,30}, 3);

     	t.get_ball().get_position().print();
    }
    {
        Ball b(Point{90, -10}, 20);
        Table t(Point{60, -80}, Point{220, 40}, Point{160, 120}, Point{0, 0}, b);

        t.strike(Point{12,-316}, 1);

        t.get_ball().get_position().print();
    }

    return 0;
}