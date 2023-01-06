#include<iostream>
#include <cmath>
#include <limits>
using namespace std;


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
		friend ostream &operator<<(ostream &os, const Point &p) {
			return os << p.x << ' ' << p.y;
		}

		float get_x() { return x; }
		float get_y() { return y; }

		float get_dist()
		{
			return sqrt(x*x+y*y);
		}
};

class Ball
{
	private:
		Point position;
		float d;
	
	public:
		Ball(Point position, float d) : position(position), d(d) { }

		Point get_position() const { return position; }
		float get_d() const { return d; }
		float get_r() const { return d/2; }
		void set_position(const Point &pos) { position = pos; }
};

const double eps = 0.000001;

class Table
{
	private:
		Ball ball;
		Point a, b, c, d;
		Point right_dir, up_dir;
		float lowc, highc, leftc, rightc;
	public:

		Table(const Point &a, const Point &b, const Point &c, const Point &d, const Ball &ball) : a(a), b(b), c(c), d(d), ball(ball)
		{
			right_dir = b-a;
			right_dir = right_dir / right_dir.get_dist();
			up_dir    = d-a;
			up_dir    = up_dir / up_dir.get_dist();

			lowc   = a*up_dir    + ball.get_r();
			highc  = d*up_dir    - ball.get_r();
			leftc  = a*right_dir + ball.get_r();
			rightc = b*right_dir - ball.get_r();
		}
		Ball get_ball() const { return ball; }
		/*
		 	ako topka udari stena ,tq rikushira
			ako udari ugul, topkata se vrushta nazad kum poziciqta ot koqto e pochnal
			ot ball.get_position() do direction e duljinata na "vectora"
			power e kolko puti vectora mu se umnojava razstoqnieto 
		 */
		float get_low_power(Point direction) const {
			if (abs(up_dir*direction) < eps) return numeric_limits<float>::infinity();
			return (lowc - up_dir*ball.get_position())/(up_dir*direction);
		}
		float get_high_power(Point direction) const {
			if (abs(up_dir*direction) < eps) return numeric_limits<float>::infinity();
			return (highc - up_dir*ball.get_position())/(up_dir*direction);
		} float get_left_power(Point direction) const { if (abs(right_dir*direction) < eps) return numeric_limits<float>::infinity();
			return (leftc - right_dir*ball.get_position())/(right_dir*direction);
		}
		float get_right_power(Point direction) const {
			if (abs(right_dir*direction) < eps) return numeric_limits<float>::infinity();
			return (rightc - right_dir*ball.get_position())/(right_dir*direction);
		}
		void strike(Point destination, float power)
		{
			Point direction = destination - ball.get_position();
			while (power > eps) {
				/* cout << "starting from position " << ball.get_position() << endl; */
				/* cout << "moving at direction " << direction << endl; */
				float pows[4] = {
					get_low_power(direction),
					get_high_power(direction),
					get_left_power(direction),
					get_right_power(direction)
				};
				int p = -1;
				for (int i=0; i<4; ++i) {
					if (pows[i] > eps && (p == -1 || pows[i] < pows[p])) {
						p = i;
					}
				}
				/* cout << "will bounce off of wall " << (p == 0? "bottom": p == 1? "top": p == 2? "left": "right") << endl; */
				/* cout << "will bounce at power " << pows[p] << endl; */
				/* cout << "actual power is " << power << endl; */
				if (pows[p] > power - eps) {
					ball.set_position(ball.get_position() + direction * power);
					return;
				}
				ball.set_position(ball.get_position() + direction * pows[p]);
				if (p == 0 || p == 1) {
					direction = direction - up_dir*2*(direction*up_dir);
				} else {
					direction = direction - right_dir*2*(direction*right_dir);
				}
				power -= pows[p];
			}
		}
};


int main()
{
	/* { */
	/* 	Ball b(Point{280, 70}, 0); */
	/* 	Table t(Point{0, 0}, Point{320, 0}, Point{320, 160}, Point{0, 160}, b); */

	/* 	t.strike(Point{230,110}, 2); */

	/* 	cout << t.get_ball().get_position() << endl; */
	/* } */
	/* { */
	/* 	Ball b(Point{300, 60}, 0); */
	/* 	Table t(Point{0, 0}, Point{320, 0}, Point{320, 160}, Point{0, 160}, b); */

	/* 	t.strike(Point{250,30}, 3); */

	/* 	cout << t.get_ball().get_position() << endl; */
	/* } */
	{
		Ball b(Point{90, -10}, 20);
		Table t(Point{60, -80}, Point{220, 40}, Point{160, 120}, Point{0, 0}, b);

		t.strike(Point{12,-316}, 1);

		cout << t.get_ball().get_position() << endl;
	}
	return 0;
}
