/**
 *  @file Point.cpp
 *  @brief Implements the class Point defined in Point.h
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#include <math.h>
#include <iomanip>      // std::setprecision

#include "Point.h"

using namespace std;

/**
 * @brief Default constructor.
 *
 * @return Point at (0, 0).
 */
Point::Point() {
  this->x = 0;
  this->y = 0;
}

/**
 * @brief Constructor for a given point at a given location.
 *
 * @param x Coordinate value.
 * @param y Coordinate value.
 * @return Point at (x, y).
 */
Point::Point(const double x, const double y) {
  this->x = x;
  this->y = y;
}

/**
 * @brief Takes vector sum of two points.
 *
 * @param other Point to add.
 * @return Point containing sum of this point and other point.
 */
Point  Point::operator + (const Point &other) const { 
  Point res; 
  res.x = this->x + other.x; 
  res.y = this->y + other.y; 
  return res; 
}

/**
 * @brief Takes vector difference of two points.
 *
 * @param other Point to subtract.
 * @return Point containing difference between this point and other point.
 */
Point Point::operator - (const Point &other) const { 
  Point res; 
  res.x = this->x - other.x; 
  res.y = this->y - other.y; 
  return res; 
}

/**
 * @brief Computes dot product of two points.
 *
 * @param other Point to dot against.
 * @return Dot product of two points.
 */
double Point::dot(const Point &other) const {
  return (this->x * other.x) + (this->y * other.y);
}

/**
 * @brief Computes cross product of two points.
 *
 * @param other Point to cross against.
 * @return Cross product of two points.
 */
double Point::cross(const Point &other) const {
  return (this->x * other.y) - (other.x * this->y);
}

/**
 * @brief Computes distance between two points.
 *
 * @param other Point to cross against.
 * @return Cross product of two points.
 */
double Point::dist(const Point &other) const {
  Point delta = other - *this;
  return sqrt(delta.dot(delta));
}

/**
 * @brief Returns whether the point is ON, the LEFT of, or the RIGHT of the
 * line passing through A and B.
 *
 * @param A First point on line.
 * @param B Second point on line.
 * @return Line side test result of current point with respect to line AB.
 */
int Point::line_side_of(const Point &A, const Point  &B) const {
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

/**
 * @brief Adds support for printing Points.
 * 
 * @param os Output stream.
 * @param p Point Object.
 * @return New output stream with point inside stream.
 */
ostream& operator<<(ostream& os, const Point& p) {
  os << fixed;
  os << setprecision(3);
  os << "(" << p.x << ", " << p.y << ")";
  return os;
}