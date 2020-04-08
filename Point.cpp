/* Point class to store (x, y) points and some utility functions for them */

#include <math.h>
#include <iomanip>      // std::setprecision

using namespace std;

class Point
{
  public:
    double x;
    double y;

    Point(double x, double y) {
      this->x = x;
      this->y = y;
    }

    friend ostream& operator<<(ostream& os, const Point& p) {
      os << fixed;
      os << setprecision(3);
      os << "(" << p.x << ", " << p.y << ")";
      return os;
    }

    double dist(Point &other) {
      float dx = (this->x) - other.x;
      float dy = (this->y) - other.y;
      return sqrt(dx * dx + dy * dy);
    }

};