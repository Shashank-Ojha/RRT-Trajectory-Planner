/* Point class to store (x, y) points and some utility functions for them */

/**
 *  @file Obstacle.h
 *  @brief Defines a class Point to keep track of (x,y) points and utility
 *  functions for them
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#ifndef __POINT_H
#define __POINT_H

#include <iostream>

/* Constants for Line-Side Test */
#define LEFT -1
#define ON 0
#define RIGHT 1

using namespace std;

class Point
{
  public:
    /* Data */
    double x;
    double y;

    /* Constructors */
    Point();
    Point(double x, double y);

    /* Function Prototypes */
    Point operator + (Point const &other);
    Point operator - (Point const &other);

    double dot(Point &other);
    double cross(Point &other);
    double dist(Point &other);
    int line_side_of(Point &A, Point &B);

    bool equals(Point *other);
    double at(int dimension);

    /* Output Stream Definition */
    friend ostream& operator<<(ostream& os, const Point& p);
};

#endif /* __POINT_H */
