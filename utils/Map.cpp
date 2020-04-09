/**
 *  @file Map.cpp
 *  @brief Implements the class Map defined in Map.h
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#include <vector>

#include "Map.h"
#include "Obstacle.h"
#include "Point.h"

using namespace std;

/**
 * @brief Default Map constructor.
 *
 * @return Map containing no obstacles.
 */
Map::Map() {
  this->num_obstacles = 0;
  this->obstacles = vector<Obstacle>();
}

/**
 * @brief Map constructor given a set of obstacles.
 *
 * @param obstacles A vector of all obstacles in map.
 * @return Map containing all obstacles given.
 */
Map::Map(vector<Obstacle> obs) {
  this->num_obstacles = obs.size();
  this->obstacles = vector<Obstacle>(obs);
}

/**
 * @brief Adds the given obstacle to the map.
 *
 * @param obstacle An Obstacle.
 * @return Void.
 */
void Map::add_obstacle(Obstacle &o) {
  this->num_obstacles += 1;
  this->obstacles.push_back(o);
}

/**
 * @brief Checks if the given point collides with any of the obstacles in the
 * Map.
 *
 * @param p A point.
 * @return True if it doesn't collid with any obstacles and False otherwise.
 */
bool Map::is_freespace(Point &p) {
  for(Obstacle &obs : this->obstacles) {
    if(obs.collides(p)) {
      return false;
    }
  }
  return true;
}