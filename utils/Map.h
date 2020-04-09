
#ifndef __MAP_H
#define __MAP_H

#include <vector>

#include "Point.h"
#include "Obstacle.h"

class Map
{
  public:
    int num_obstacles;
    vector<Obstacle> obstacles;

    Map();
    Map(vector<Obstacle> obstacles);

    void add_obstacle(Obstacle &obs);
    bool is_freespace(Point &p);
};

#endif /* __MAP_H */
