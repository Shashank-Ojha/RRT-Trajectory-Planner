
/**
 *  @file Map.h
 *  @brief Defines a class Map containing all information about space
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#ifndef __MAP_H
#define __MAP_H

#include <vector>

#include "Point.h"
#include "Obstacle.h"

class Map
{
  public:
    /* Data */
    int num_obstacles;
    vector<Obstacle> obstacles;

    /* Constructors */
    Map();
    Map(vector<Obstacle> obs);

    /* Function Prototypes */
    void add_obstacle(Obstacle &o);
    bool is_freespace(Point &p);
};

#endif /* __MAP_H */
