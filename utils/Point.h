/* Point class to store (x, y) points and some utility functions for them */

#ifndef __POINT_H
#define __POINT_H

#define LEFT -1
#define ON 0
#define RIGHT 1

using namespace std;

class Point
{
  public:
    double x;
    double y;

    Point();
    Point(double x, double y);

    Point operator + (Point const &other);
    Point operator - (Point const &other);

    double dot(Point &other);
    double cross(Point &other);
    int line_side_of(Point &A, Point &B);
    double dist(Point &other);

    friend ostream& operator<<(ostream& os, const Point& p);
};

#endif /* __POINT_H */
