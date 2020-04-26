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
#include <fstream>

#include "Map.h"
#include "Obstacle.h"
#include "Point.h"

using namespace std;

/**
 * @brief Default Map constructor.
 *
 * @param robot_radius Radius of Robot.
 * @return Map containing no obstacles.
 */
Map::Map(const float &robot_radius) {
  this->rad = robot_radius;
  this->num_obstacles = 0;
  this->obstacles = vector<Obstacle>();
}

/**
 * @brief Map constructor given a set of obstacles.
 *
 * @param robot_radius Radius of Robot.
 * @param obstacles A vector of all obstacles in map.
 * @return Map containing all obstacles given.
 */
Map::Map(const float &robot_radius, const vector<Obstacle> &obs) {
  this->rad = robot_radius;
  this->num_obstacles = obs.size();
  this->obstacles = vector<Obstacle>(obs);
}

/**
 * @brief Map constructor that reads data from file.
 *
 * @param robot_radius Radius of Robot.s
 * @param filename The file to read from.
 * @return Map containing all data given in file.
 */
Map::Map(const float &robot_radius, const string &filename) {
  this->rad = robot_radius;

  ifstream infile;
  infile.open(filename);

  if (!infile) {
    throw std::invalid_argument( "Map Constructor: Unable to open file!");
  }

  infile >> this->height;
  infile >> this->width;

  infile >> this->num_obstacles;

  for (int i = 0; i < this->num_obstacles; i++) {
    vector<Point> polygon;
    int n;
    infile >> n;
    for (int j = 0; j < n; j++) {
      float x, y;
      infile >> x;
      infile >> y;
      polygon.push_back(Point(x, y));
    } 
    Obstacle o(polygon);
    this->obstacles.push_back(o);
    this->minkowski.push_back(Obstacle::minkowski_sum(o, this->rad));
    polygon.clear();    
  }
}


/**
 * @brief Adds the given obstacle to the map.
 *
 * @param obstacle An Obstacle.
 * @return Void.
 */
void Map::add_obstacle(const Obstacle &o) {
  this->num_obstacles += 1;
  this->obstacles.push_back(o);
  this->minkowski.push_back(Obstacle::minkowski_sum(o, this->rad));
}

/**
 * @brief Checks if the given point collides with any of the obstacles in the
 * Map.
 *
 * @param p A point.
 * @return True if it doesn't collid with any obstacles and false otherwise.
 */
bool Map::is_freespace(const Point &p) const {
  for(const Obstacle &obs : this->minkowski) {
    if(obs.collides(p)) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Checks if the given path collides with any of the obstacles in the
 * Map.
 *
 * @param p1 First point on path.
 * @param p2 Second point on path.
 * @return True if it doesn't collid with any obstacles and false otherwise.
 */
bool Map::is_valid_path(const Point &p1, const Point &p2) const {
  for(const Obstacle &obs : this->minkowski) {
    if(obs.path_collides(p1, p2)) {
      return false;
    }
  }
  return true;
}