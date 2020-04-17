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

using namespace std;

#define POINT_EPSILON 0.000000001

class Point {
  public:
    /* Data */
    double x;
    double y;

    /* Constructors */
    Point();
    Point(const double x, const double y);
    Point(const Point &other);

    /* Function Prototypes */
    Point operator + (const Point &other) const;
    Point operator - (const Point &other) const;
    bool operator == (const Point &other) const;
    double operator [] (int dimension) const;

    double dot(const Point &other) const;
    double cross(const Point &other) const;
    double dist(const Point &other) const;
    double angle(const Point &other) const;

    bool equals(Point *other);
    double at(int dimension);

    /* Output Stream Definition */
    friend ostream& operator<<(ostream& os, const Point& p);
};

#endif /* __POINT_H */
