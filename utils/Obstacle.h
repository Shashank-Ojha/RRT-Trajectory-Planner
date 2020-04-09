
#ifndef __OBSTACLE_H
#define __OBSTACLE_H

#include <vector>

#include "Point.h"

class Obstacle
{
  public:
    vector<Point> convex_hull;

    Obstacle(vector<Point> &polygon);

    bool is_convex_hull(vector<Point> &polygon);
    bool collides(Point &p);
};

#endif /* __OBSTACLE_H */
