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

class Obstacle
{
  public:
    /* Data */
    vector<Point> convex_hull;

    /* Constructors */
    Obstacle(vector<Point> &polygon);

    /* Function Prototypes */
    bool is_convex_hull(vector<Point> &polygon);
    bool collides(Point &p);
};

#endif /* __OBSTACLE_H */
