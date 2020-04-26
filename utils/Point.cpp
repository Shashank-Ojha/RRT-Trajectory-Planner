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
 * @brief Copy constructor.
 *
 * @param p Coordinate value.
 * @return Point at (x, y).
 */
Point::Point(const Point &other) {
  this->x = other.x;
  this->y = other.y;
}

/**
 * @brief Takes vector sum of two points.
 *
 * @param other Point to add.
 * @return Point containing sum of this point and other point.
 */
Point Point::operator + (const Point &other) const {
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
 * @return Distance between two points.
 */
double Point::dist(const Point &other) const {
  Point delta = other - *this;
  return sqrt(delta.dot(delta));
}

/**
 * @brief Computes angle between two points.
 *
 * @param other Point to find the angle to.
 * @return Angle between horizontal at current point and other point in radians
 */
double Point::angle(const Point &other) const {
    double r = this->dist(other);
    double dx = other.x - this->x;
    double angle = acos (dx / r);
    if (this->y > other.y) {
        angle *= -1;
    }
    return angle;
}

/**
 * @brief Normalizes the point to the sum of its value is 1.
 *
 * @return Normalized point.
 */
Point Point::normalize() const {
    double norm = sqrt(this->dot(*this));
    double new_x = (this->x) / norm;
    double new_y = (this->y) / norm;
    return Point(new_x, new_y);
}

/**
 * @brief Scales the point by s.
 *
 * @param s Scale factor.
 * @return Scaled point.
 */
Point Point::scale(const double &s) const {
    return Point(s * (this->x), s * (this->y));
}

/**
 * @brief Checks for equality between doubles. We define equality between  
 * doubles if their absolute difference is less than a predefined EPSILON.
 *
 * @param x 1st double
 * @param y 2nd double
 * @return True if equal and false otherwise.
 */
bool double_equals(double x, double y) {
  return fabs(x - y) < POINT_EPSILON;
}

/**
 * @brief Checks for equality between points.
 *
 * @param other Point to check equality against.
 * @return True if equal and false otherwise.
 */
bool Point::operator == (const Point &other) const {
  return double_equals(this->x, other.x) && double_equals(this->y, other.y);
}


/**
 * @brief Accesses the value of the point at the dimension given.
 *
 * @param dimension Dimension to access.
 * @return True if equal and false otherwise.
 */
double Point::at(int dimension){
  if (dimension == 0) return this->x;
  else return this->y;
}

/**
 * @brief Accesses the value of the point at the dimension given.
 *
 * @param dim Dimension to access.
 * @return True if equal and false otherwise.
 */
double Point::operator [] (const int dimension) const { 
  if (dimension == 0) return this->x;
  if (dimension == 1) return this->y;
  throw std::invalid_argument( "Point Operator [] received invalid dimension");
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
