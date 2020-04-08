/* Point class to store (x, y) points and some utility functions for them */

#include <math.h>

class Point
{
  public:
    double x;
    double y;

    Point(double x, double y) {
      this -> x = x;
      this -> y = y;
    }

    double dist(Point &other) {
      float dx = (this -> x) - other.x;
      float dy = (this -> y) - other.y;
      return sqrt(dx * dx + dy * dy);
    }

};