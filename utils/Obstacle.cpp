
#include <vector>

#include "Obstacle.h"
#include "Point.h"


Obstacle::Obstacle(vector<Point> &polygon) {
  assert(is_convex_hull(polygon));
  convex_hull = vector<Point>(polygon);
}

/*
  Checks whether the set of points in the polygon form a convex hull. 

*/
bool Obstacle::is_convex_hull(vector<Point> &polygon) {
  int n = polygon.size();
  if (n <= 1) { return false; }
  if (n == 2) { return true; }

  int prev_result = 0;
  for (int i = 0; i < n; i++) {
    Point &A = polygon[i];
    Point &B = polygon[(i+1) % n];
    Point &C = polygon[(i+2) % n];

    int result = C.line_side_of(A, B);
    // Skip first check because no prev_result
    if(i != 0 && (result == ON || result != prev_result)) {
      return false;
    }
    prev_result = result;
  }

  return true;
}

/*
  Checks whether the given point p is inside the obstacle. This 
  only works because the obstacle  is assumed to be convex.
*/
bool Obstacle::collides(Point &p) {
  int n = this->convex_hull.size();

  int violations = 0;
  for (int i = 0; i < n; i++) {
    Point &A = this->convex_hull[i];
    Point &B = this->convex_hull[(i+1) % n];

    if(p.line_side_of(A, B) != RIGHT) {
      violations += 1;
    }
  }
  return violations == n;
}
