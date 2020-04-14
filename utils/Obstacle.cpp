/**
 *  @file Obstacle.cpp
 *  @brief Implements the class Obstacle defined in Obstacle.h
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick ss(dbick)
 *  @bug No known bugs.
 */

#include <vector>

#include "Obstacle.h"
#include "Point.h"

/**
 * @brief Obstacle constructor given vector of points.
 *
 * @param polygon vector of points defining convex polygon.
 * @return Obstacle containing given points.
 */
Obstacle::Obstacle(const vector<Point> &polygon) {
  assert(is_convex_hull(polygon));
  convex_hull = vector<Point>(polygon);
}

/**
 * @brief Checks whether the set of points in the polygon form a convex hull.
 *
 * @param polygon vector of points defining some polygon.
 * @return True if the points form a convex polygon and False otherwise.
 */
bool Obstacle::is_convex_hull(const vector<Point> &polygon) {
  int n = polygon.size();
  if (n <= 1) { return false; }
  if (n == 2) { return true; }

  int prev_result = 0;
  for (int i = 0; i < n; i++) {
    const Point &A = polygon[i];
    const Point &B = polygon[(i+1) % n];
    const Point &C = polygon[(i+2) % n];

    int result = C.line_side_of(A, B);
    // Skip first check because no prev_result
    if(i != 0 && (result == ON || result != prev_result)) {
      return false;
    }
    prev_result = result;
  }

  return true;
}


/**
 * @brief Checks whether the given point p is inside the obstacle. This only
 * works because the obstacle is assumed to be convex.
 *
 * @param p A Point to check.
 * @return True if the point lies on or inside the obstacle and False otherwise.
 */
bool Obstacle::collides(const Point &p) const {
  int n = this->convex_hull.size();

  int cc_violations = 0; /* counter-clockwise assumption */
  int c_violations = 0;  /* clockwise assumption */
  for (int i = 0; i < n; i++) {
    const Point &A = this->convex_hull[i];
    const Point &B = this->convex_hull[(i+1) % n];

    if(p.line_side_of(A, B) != RIGHT) {
      cc_violations += 1;
    }

    if(p.line_side_of(A, B) != LEFT) {
      c_violations += 1;
    }
  }
  return cc_violations == n || c_violations == n;
}
