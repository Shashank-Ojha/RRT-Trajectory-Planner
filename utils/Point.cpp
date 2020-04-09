/* Point class to store (x, y) points and some utility functions for them */

#include <math.h>
#include <iomanip>      // std::setprecision

#include "Point.h"

using namespace std;

Point::Point() {
  this->x = 0;
  this->y = 0;
}

Point::Point(double x, double y) {
  this->x = x;
  this->y = y;
}


/*
  Returns the sum with the other point
*/
Point Point::operator + (Point const &other) { 
      Point res; 
      res.x = this->x + other.x; 
      res.y = this->y + other.y; 
      return res; 
}

/*
  Returns the difference with the other point
*/
Point Point::operator - (Point const &other) { 
      Point res; 
      res.x = this->x - other.x; 
      res.y = this->y - other.y; 
      return res; 
}

/*
  Returns the dot product with the other point
*/
double Point::dot(Point &other) {
  return (this->x * other.x) + (this->y * other.y);
}

/*
  Returns the cross product with the other point
*/
double Point::cross(Point &other) {
  return (this->x * other.y) - (other.x * this->y);
}

/*
  Returns whether the point is ON, the LEFT of, or the RIGHT of the
  line passing through A and B
*/
int Point::line_side_of(Point &A, Point &B) {
  Point line = B - A;
  Point error = *this - A;
  double cross_prod = line.cross(error);
  if (cross_prod > 0) {
    return LEFT;
  }
  else if (cross_prod < 0) {
    return RIGHT;
  }
  return ON;
}

double Point::dist(Point &other) {
  Point delta = other - *this;
  return sqrt(delta.dot(delta));
}

ostream& operator<<(ostream& os, const Point& p) {
  os << fixed;
  os << setprecision(3);
  os << "(" << p.x << ", " << p.y << ")";
  return os;
}