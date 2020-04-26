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
 * @brief Returns whether the test point is ON, the LEFT of, or the RIGHT of
 * the line passing through A and B.
 *
 * @param test Point to test.
 * @param A First point on line.
 * @param B Second point on line.
 * @return Line side test result of current point with respect to line AB.
 */
int line_side_test(const Point &test, const Point &A, const Point &B) {
  Point line = B - A;
  Point error = test - A;
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

    int result = line_side_test(C, A, B);
    // Skip first check because no prev_result
    if(i != 0 && (result == ON || result != prev_result)) {
      return false;
    }
    prev_result = result;
  }

  return true;
}

/**
 * @brief Returns new convex hull that has been expanded by radius r.
 *
 * @param obstacle The original obstacle.
 * @param rad The radius to expand with.
 * @return True if the points form a convex polygon and False otherwise.
 */
Obstacle Obstacle::minkowski_sum(const Obstacle &o, double rad) {
  int n = o.convex_hull.size();
  vector<Point> polygon;
  for (int i = 0; i < n; i++) {
    const Point &prev = o.convex_hull[(i + n - 1) % n];
    const Point &curr = o.convex_hull[i % n];
    const Point &next = o.convex_hull[(i + 1) % n];

    Point delta1 = (curr - prev).normalize();
    Point delta2 = (curr - next).normalize();

    Point new_point = curr + delta1.scale(rad) + delta2.scale(rad);
    cout << new_point << endl;
    polygon.push_back(new_point);
  }
  return Obstacle(polygon);
}

/**
 * @brief Checks if the segment AB intersects the segment CD
 *
 * @param A Point A
 * @param B Point B
 * @param C Point C
 * @param D Point D
 * @return True if the segments intersect and False otherwise
 */
bool segments_intersect(const Point &A, const Point &B, 
                        const Point &C, const Point &D) {
  bool AB_opp_sides = (line_side_test(A, C, D) != line_side_test(B, C, D));
  bool CD_opp_sides = (line_side_test(C, A, B) != line_side_test(D, A, B));
  return AB_opp_sides && CD_opp_sides;
}

/**
 * @brief Checks whether the given point p is inside the obstacle. This only
 * works because the obstacle is assumed to be convex.
 *
 * @param p A Point to check.
 * @return True if the point lies on or inside the obstacle and false otherwise.
 */
bool Obstacle::collides(const Point &p) const {
  int n = this->convex_hull.size();

  int cc_violations = 0; /* counter-clockwise assumption */
  int c_violations = 0;  /* clockwise assumption */
  for (int i = 0; i < n; i++) {
    const Point &A = this->convex_hull[i];
    const Point &B = this->convex_hull[(i+1) % n];

    if(line_side_test(p, A, B) != RIGHT) {
      cc_violations += 1;
    }

    if(line_side_test(p, A, B) != LEFT) {
      c_violations += 1;
    }
  }
  return cc_violations == n || c_violations == n;
}

/**
 * @brief Checks whether the given point p is inside the obstacle. This only
 * works because the obstacle is assumed to be convex.
 *
 * @param p1 First point on path.
 * @param p2 Second point on path.
 * @return True if the point lies on or inside the obstacle and False otherwise.
 */
bool Obstacle::path_collides(const Point &p1, const Point &p2) const {
  int n = this->convex_hull.size();

  for (int i = 0; i < n; i++) {
    const Point &A = this->convex_hull[i];
    const Point &B = this->convex_hull[(i+1) % n];

    if(segments_intersect(p1, p2, A, B)) {
      return true;
    }
    
  }
  return false;
}
