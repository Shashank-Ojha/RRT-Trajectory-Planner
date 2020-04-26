
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

class Map {
  public:
    /* Data */
    float height;
    float width;
    int num_obstacles;
    float rad; /* Used to compute minkowski sum */
    vector<Obstacle> obstacles;
    vector<Obstacle> minkowski;

    /* Constructors */
    Map(const float &robot_radius);
    Map(const float &robot_radius, const vector<Obstacle> &obs);
    Map(const float &robot_radius, const string &filename);

    /* Function Prototypes */
    void add_obstacle(const Obstacle &o);
    bool is_freespace(const Point &p) const;
    bool is_valid_path(const Point &p1, const Point &p2) const;
};

#endif /* __MAP_H */
