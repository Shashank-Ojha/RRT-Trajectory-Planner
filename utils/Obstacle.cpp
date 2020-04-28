/**
 *  @file Obstacle.cpp
 *  @brief Implements the class Obstacle defined in Obstacle.h
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug get_convex_hull fails with repeated points.
 */

#include <unordered_map>
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

  bool dir_chosen = false;
  int dir = ON;
  for (int i = 0; i < n; i++) {
    const Point &A = polygon[i];
    const Point &B = polygon[(i+1) % n];
    const Point &C = polygon[(i+2) % n];

    int result = line_side_test(C, A, B);
    // Skip first check because no prev_result
    if(i != 0 && dir_chosen && result != ON && result != dir) {
      return false;
    }
    if (!dir_chosen && result != ON) {
      dir_chosen = true;
      dir = result;
    }
  }

  return true;
}


/**
 * @brief Get convex hull of a set of points.
 *
 * @param polygon set of points.
 * @return Ordered vector of points defining the convex hull of the input.
 */
vector<Point> get_convex_hull(const vector<Point> &polygon) {
  int n = polygon.size();
  unordered_map<int, int> edge; 
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) { continue; }
      bool proper = true;
      for (int k = 0; k < n; k++) {
        if(k == i || k == j) { continue; }
        const Point &a = polygon[i];
        const Point &b = polygon[j];
        const Point &c = polygon[k];

        if(line_side_test(c, a, b) == RIGHT) { 
          proper = false;
          break; 
        }
      }
      if(proper) {
        edge[i] = j;
      }
    }
  }

  int first = edge.begin()->first;
  int idx = first;
  vector<Point> convex_hull;
  convex_hull.push_back(polygon[idx]);
  idx = edge[idx];
  while(idx != first) {
    convex_hull.push_back(polygon[idx]);
    idx = edge[idx];
  }

  return convex_hull;
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
  vector<Point> robot_set;
  robot_set.push_back(Point(rad, rad));
  robot_set.push_back(Point(rad, -rad));
  robot_set.push_back(Point(-rad, rad));
  robot_set.push_back(Point(-rad, -rad));

  vector<Point> minkowski;
  for (Point a : robot_set) {
    for (Point b : o.convex_hull) {
      minkowski.push_back(a + b);
    }
  }

  return Obstacle(get_convex_hull(minkowski));
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
