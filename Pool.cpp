#include<iostream>
#include<math.h>

using namespace std;


class Point
{
	private:
		float x, y;

	public:
        
        Point() { }
        
        Point(float x, float y)
        {
            this->x = x;
            this->y = y;
        }

		Point operator+(const Point &p) const { return {x+p.x, y+p.y}; }
		Point operator-(const Point &p) const { return {x-p.x, y-p.y}; }
		Point operator*(float c) const { return {c*x, c*y}; }
		Point operator/(float c) const { return {x/c, y/c}; }
		float operator*(const Point &p) const { return x*p.x + y*p.y; }

		float get_x() { return x; }
		float get_y() { return y; }

		float get_dist(Point other)
		{
			float rx = x - other.get_x(), ry = y - other.get_y();
			return sqrt(rx*rx + ry*ry);
		}
};

class Ball
{
	private:
		Point position;
		float d;
	
	public:
		Point get_position() const { return position; }
		float get_d() const { return d; }
		float set_position(const Point &pos) { position = pos; }
};


class Line
{
	private:
		Point a, b;
	
	public:

		Point get_a() { return a; }
		Point get_b() { return b; }
		
		bool are_lines_colliding(Line &other, Point &intersection)
		{
			return false;
		}
};

class Table
{
	private:
		Ball ball;
		Point a, b, c, d;
		Point right_dir, up_dir;
		float lowc, highc, leftc, rightc;
	public:

		Table() : Table(Point{-1,-1}, Point{1,-1}, Point{1,1}, Point{-1,1}) {  }

		Table(const Point &a, const Point &b, const Point &c, const Point &d)
		{
			this->a = a;
			this->b = b;
			this->c = c;
			this->d = d;
            
			right_dir = b-a;
			right_dir = right_dir / right_dir.get_dist();
			up_dir    = d-c;
			up_dir    = up_dir / up_dir.get_dist();
            
			lowc   = a*up_dir    + ball.get_d();
			highc  = d*up_dir    - ball.get_d();
			leftc  = a*right_dir + ball.get_d();
			rightc = b*right_dir - ball.get_d();
		}
		
        /*
		 	ako topka udari stena ,tq rikushira
			ako udari ugul, topkata se vrushta nazad kum poziciqta ot koqto e pochnal
			ot ball.get_position() do direction e duljinata na "vectora"
			power e kolko puti vectora mu se umnojava razstoqnieto 
		 */
		
        float get_low_power(Point direction) const { return lowc - (up_dir*ball.get_position())/(up_dir*direction); }
		float get_high_power(Point direction) const { return highc - (up_dir*ball.get_position())/(up_dir*direction); }
		float get_left_power(Point direction) const { return leftc - (right_dir*ball.get_position())/(right_dir*direction); }
		float get_right_power(Point direction) const { return rightc - (right_dir*ball.get_position())/(right_dir*direction);  }
        
		void strike(Point direction, float power)
		{
			while (power > 0.000000001) 
            {
				
                float pows[4] = {
					get_low_power(direction),
					get_high_power(direction),
					get_left_power(direction),
					get_right_power(direction)
				};
                
				int p = -1;
				for (int i=0; i<4; ++i) 
					if (pows[i] >= 0 && (p == -1 || pows[i] < pows[p]))
						p = i;
                
				if (p == 0 || p == 1) 
					direction = direction - 2*up_dir*(direction*up_dir);
				
				 else 
					direction = direction - 2*right_dir*(direction*right_dir);
				
				ball.set_position(ball.get_position() + direction * pows[p]);
				power -= pows[p];
			}
		}
};


int main()
{



	return 0;
}
