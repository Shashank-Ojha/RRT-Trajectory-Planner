/**
 *  @file Obstacle.h
 *  @brief Defines a class Obstacle containing all information about an obstacle
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#ifndef __OBSTACLE_H
#define __OBSTACLE_H

#include <vector>

#include "Point.h"

/* Constants for Line-Side Test (used internally) */
#define LEFT -1
#define ON 0
#define RIGHT 1

class Obstacle {
  public:
    /* Data */
    vector<Point> convex_hull;

    /* Constructors */
    Obstacle(const vector<Point> &polygon);

    /* Function Prototypes */
    static bool is_convex_hull(const vector<Point> &polygon);
    bool collides(const Point &p) const;
    bool path_collides(const Point &p1, const Point &p2) const;
};

#endif /* __OBSTACLE_H */
